//
// Copyright (c) 2016, minyor.
//
// License:	BSD
//


#include <Poco/Random.h>
#include <Poco/Crypto/RSADigestEngine.h>
#include <Poco/SharedPtr.h>
#include <Poco/Net/InvalidCertificateHandler.h>
#include <Poco/Net/AcceptCertificateHandler.h>
#include <Poco/Net/ConsoleCertificateHandler.h>
#include <Poco/Net/Context.h>
#include <Poco/Net/SSLManager.h>
#include <Poco/Net/SMTPClientSession.h>
#include <Poco/Net/SecureSMTPClientSession.h>
#include <Poco/Net/SecureStreamSocket.h>
#include <Poco/Net/MailMessage.h>

#include <sstream>
#include <iomanip>

#include <core/Header.h>
#include <core/Util.h>


using namespace core::util;


std::string core::dateFormat()
{
	return core::server().conf().dateFormat();
}
std::int32_t core::dateTimeZone()
{
	return core::server().conf().dateTimeZone();
}


namespace
{
	struct SaltRange
	{
		const static std::uint32_t size = 64;
		char map[size];

		SaltRange()
		{
			std::uint32_t i = 0;
			for(char c='0'; c<='9'; ++c) map[i++] = c;
			for(char c='A'; c<='Z'; ++c) map[i++] = c;
			for(char c='a'; c<='z'; ++c) map[i++] = c;
			map[i++] = '_';
			map[i++] = '.';
		}
	};
}

std::string Hash::salt(std::uint32_t size)
{
	static SaltRange saltRange;
	std::string salt;
	Poco::Random random; random.seed();
	for(std::uint32_t i=0; i<size; ++i)
		salt += saltRange.map[random.next(SaltRange::size)];
	return salt;
}

std::string Hash::hash(const std::string &in)
{
	using namespace Poco::Crypto;

	struct CryptoInit { CryptoInit() { Poco::Crypto::initializeCrypto(); } };
	static CryptoInit cryptoInit;

	RSAKey key(RSAKey::KL_2048, RSAKey::EXP_LARGE);
	/*std::string publicKeyFile, privateKeyFile, privateKeyPassphrase;
	key.save(publicKeyFile, privateKeyFile, privateKeyPassphrase);
	printff("publicKeyFile='%s'\n", publicKeyFile.c_str());
	printff("privateKeyFile='%s'\n", privateKeyFile.c_str());
	printff("privateKeyPassphrase='%s'\n", privateKeyPassphrase.c_str());*/

	RSADigestEngine engine(key, "SHA256");
	engine.update(in);
	auto digest = engine.digest();
	std::stringstream out;
	for(std::uint32_t i=0; i<digest.size(); ++i)
		out << std::hex << std::setw(2) << std::setfill('0') << (int)digest[i];
	return out.str();
}

bool Hash::isEqual(const std::string &a, const std::string &b)
{
	if(a.size() != b.size()) return false;
	int result = 0;
	for(size_t i=0; i<a.size(); ++i)
		result |= a[i] ^ b[i];
	return result == 0;
}


typedef const char *FormatPtr;

namespace
{
	class EmoticonData
	{
	public:
		struct Map
		{
			typedef std::pair<const std::string, std::string> Pair;

			std::map<std::string, std::string> map;
			std::size_t maxLen;

			__inline Map() : maxLen(0) {}
			__inline std::map<std::string, std::string> &operator()() { return map; }
		};

	private:
		const static std::uint32_t TABLE_SIZE = 128;
		typedef std::uint16_t TableType, *TableTypePtr;

		std::size_t _size;
		core::Vector<Map> _lexems;
		TableType **_table;

	private:
		EmoticonData() : _size(0), _table(NULL) {}

	public:
		static EmoticonData &instance()
		{
			static EmoticonData data;

			if(data._size == core::server().conf().emoticons()->size())
				return data;
			data._size = core::server().conf().emoticons()->size();

			if(data._table) for(std::uint32_t i=0; i<TABLE_SIZE; ++i) delete[] data._table[i];
			delete[] data._table;

			data._table = new TableTypePtr[TABLE_SIZE];
			for(std::uint32_t i=0; i<TABLE_SIZE; ++i) data._table[i] = NULL;

			auto vec = core::server().conf().emoticons();
			for(std::size_t e=0; e<vec->size(); ++e)
			{
				core::Config::Emoticon &emo = *vec()[e];
				if(emo.name.size() < 2 || emo.name.c_str()[0] >= TABLE_SIZE || emo.name.c_str()[1] >= TABLE_SIZE)
					continue;

				TableTypePtr &ptr = data._table[emo.name.c_str()[0]];
				if(!ptr) {
					ptr = new TableType[TABLE_SIZE];
					for(std::uint32_t i=0; i<TABLE_SIZE; ++i) ptr[i] = TableType(-1);
				}

				TableType &ind = ptr[emo.name.c_str()[1]];
				if(ind == TableType(-1)) {
					if(data._lexems->size() >= std::numeric_limits<TableType>::max()) continue;
					data._lexems.add(new Map);
					ind = data._lexems->size() - 1;
				}

				auto &map = *data._lexems.me()[ind];
				map()[emo.name] = emo.src;
				map.maxLen = std::max(map.maxLen, emo.name.size());
			}

			return data;
		}

	public:
		__inline Map *map(const char *key)
		{
			if(key[0] >= TABLE_SIZE) return NULL;
			TableTypePtr &ptr = _table[key[0]];
			if(!ptr || key[1] >= TABLE_SIZE) return NULL;
			TableType &ind = ptr[key[1]];
			if(ind == TableType(-1)) return NULL;
			return &(*_lexems.me()[ind]);
		}

	};
}

static void bbcode(std::string &out, FormatPtr &p)
{
	struct BBCode
	{
		std::string &out; FormatPtr &p;
		const char *_b, *_m, *_m2, *_e;
		BBCode(std::string &out, FormatPtr &p) : out(out), p(p) {}

		__inline std::string parse(const char *_ptr, int _size) {
			return Html::format(std::string(_ptr, _size));
		}
		__inline void skipNewLine() const { bool n1 = p[1]==10, n2 = p[1]==13;
			if(n1 || n2) { ++p; if((p[1]==10 && n2) || (p[1]==13 && n1)) ++p; }
		}
		__inline bool parameterless(const char *_end, int _size) {
			_b = _m = _m2 = p + _size + 1;
			_e = strstr(_b, _end); if(!_e) return false;
			p = _e + _size + 2; return true;
		}
		__inline bool parameter(const char *_mid, const char *_end, int _sbeg, int _send) {
			_b = p + _sbeg + 1;
			_m = strstr(_b, _mid); if(!_m) return false; _m2 = _m + 1;
			_e = strstr(_m, _end); if(!_e) return false;
			p = _e + _send + 2; if(_b[0]=='\"' || _b[0]=='\'') { ++_b; --_m; } return true;
		}
		__inline void b() { if(!parameterless("[/b]", 1)) return;
			out.append("<b>").append(parse(_b, _e - _b)).append("</b>");
		}
		__inline void i() { if(!parameterless("[/i]", 1)) return;
			out.append("<i>").append(parse(_b, _e - _b)).append("</i>");
		}
		__inline void img() { if(!parameterless("[/img]", 3)) return;
			out.append("<img src=\"").append(_b, _e - _b).append("\" alt=\"\" />");
		}
		__inline void u() { if(!parameterless("[/u]", 1)) return;
			out.append("<u>").append(parse(_b, _e - _b)).append("</u>");
		}
		__inline void url() { if(!parameterless("[/url]", 3)) return;
			out.append("<a target='_blank' href=\"").append(_b, _e - _b).append("\">").append(_b, _e - _b).append("</a>");
		}
		__inline void url(bool par) { (void)par; if(!parameter("]", "[/url]", 3, 3)) return;
			out.append("<a target='_blank' href=\"").append(_b, _m - _b).append("\">").append(_m2, _e - _m2).append("</a>");
		}
		__inline void s() { if(!parameterless("[/s]", 1)) return;
			out.append("<s>").append(parse(_b, _e - _b)).append("</s>");
		}
		__inline void size() { if(!parameter("]", "[/size]", 4, 4)) return;
			out.append("<span style=\"font-size:").append(_b, _m - _b).append("\">").append(parse(_m2, _e - _m2)).append("</span>");
		}
		__inline void style_size() { if(!parameter("]", "[/style]", 10, 5)) return;
			out.append("<span style=\"font-size:").append(_b, _m - _b).append("\">").append(parse(_m2, _e - _m2)).append("</span>");
		}
		__inline void style_color_alias() { if(!parameter("]", "[/style]", 11, 5)) return;
			out.append("<span style=\"color:").append(_b, _m - _b).append("\">").append(parse(_m2, _e - _m2)).append("</span>");
		}
		__inline void style_color_hex() { if(!parameter("]", "[/style]", 12, 5)) return;
			out.append("<span style=\"color:#").append(_b, _m - _b).append("\">").append(parse(_m2, _e - _m2)).append("</span>");
		}
		__inline void quote() { if(!parameterless("[/quote]", 5)) return;
			out.append("<blockquote><p>").append(parse(_b, _e - _b)).append("</p></blockquote>"); skipNewLine();
		}
		__inline void quote(bool par) { (void)par; if(!parameter("]", "[/quote]", 5, 5)) return;
			out.append("<blockquote><p>").append(parse(_m2, _e - _m2)).append("</p></blockquote>"); skipNewLine();
		}
		__inline void code() { if(!parameterless("[/code]", 4)) return;
			out.append("<pre>").append(parse(_b, _e - _b)).append("</pre>"); skipNewLine();
		}
		__inline void color_alias() { if(!parameter("]", "[/color]", 5, 5)) return;
			out.append("<span style=\"color:").append(_b, _m - _b).append("\">").append(parse(_m2, _e - _m2)).append("</span>");
		}
		__inline void color_hex() { if(!parameter("]", "[/color]", 6, 5)) return;
			out.append("<span style=\"color:#").append(_b, _m - _b).append("\">").append(parse(_m2, _e - _m2)).append("</span>");
		}
		__inline bool list_li(const char *_li, int _size) { const char *_c = _m2, *_n, *_nn = NULL;
			while(((_n=strstr(_c, _li)) || (_n=_nn)) && _n<_e) { _n += _size; _c = _n;
				_nn = strstr(_n, _li); if(!_nn || _nn>_e) _nn = _e;
				out.append("<li>").append(parse(_n, _nn - _n)).append("</li>");
			} return _c!=_m2;
		}
		__inline void list_li() { if(list_li("[*]", 3)) return;
			list_li("*", 1);
		}
		__inline void list() { if(!parameterless("[/list]", 4)) return;
			out.append("<ul>"); list_li(); out.append("</ul>"); skipNewLine();
		}
		__inline void list(bool par) { (void)par; if(!parameter("]", "[/list]", 4, 4)) return;
			out.append("<ol type=\"").append(_b, _m - _b).append("\">"); list_li(); out.append("</ol>"); skipNewLine();
		}
		__inline void bbcode_table(FormatPtr &p) { ++p; if(p[0] != 't' || p[2] != ']') return;
			switch(p[1]) { case 'h': th(); break; case 'r': tr(); break; case 'd': td(); break; }
		}
		__inline void parse_table(const char *_ptr, int _size) { const char *save = p;
			std::string in(_ptr, _size); p = in.c_str();
			for(bool run=1; run; ++p) { switch(*p) { case '\0': run = 0; break; case '[': bbcode_table(p); break; }
			} p = save;
		}
		__inline void th() { if(!parameterless("[/th]", 2)) return;
			out.append("<th>").append(parse(_b, _e - _b)).append("</th>");
		}
		__inline void td() { if(!parameterless("[/td]", 2)) return;
			out.append("<td>").append(parse(_b, _e - _b)).append("</td>");
		}
		__inline void tr() { if(!parameterless("[/tr]", 2)) return;
			out.append("<tr>"); parse_table(_b, _e - _b); out.append("</tr>");
		}
		__inline void table() { if(!parameterless("[/table]", 5)) return;
			out.append("<table>"); parse_table(_b, _e - _b); out.append("</table>"); skipNewLine();
		}
	} l(out, p);

	const char *save = ++p;
	switch(*p)
	{
	case 'b': if(p[1]==']') l.b(); break;
	case 'i': if(p[1]==']') l.i(); else if(p==strstr(p, "img]")) l.img(); break;
	case 'u': if(p[1]==']') l.u(); else if(p==strstr(p, "url")) { if(p[3]==']') l.url(); else if(p[3]=='=') l.url(1); } break;
	case 's': if(p[1]==']') l.s(); else if(p==strstr(p, "size=")) { l.size(); } else if(p==strstr(p, "style ")) {
		if((p+6)==strstr(p+6, "size=")) l.style_size(); else if((p+6)==strstr(p+6, "color=#")) l.style_color_hex(); else
			if((p+6)==strstr(p+6, "color=")) l.style_color_alias(); } break;
	case 'q': if(p[1]!='u') break; if(p==strstr(p, "quote")) { if(p[5]==']') l.quote(); else if(p[5]=='=') l.quote(1); } break;
	case 'c': if(p[1]!='o') break; if(p==strstr(p, "code]")) l.code(); else
		if(p==strstr(p, "color=")) { if(p[6]=='#') l.color_hex(); else l.color_alias(); } break;
	case 'l': if(p[1]!='i') break; if(p==strstr(p, "list")) { if(p[4]==']') l.list(); else if(p[4]=='=') l.list(1); } break;
	case 't': if(p[1]!='a') break; if(p==strstr(p, "table]")) l.table(); break;
	}
	if(save == p) out += *(--p);
}

std::string Html::format(const std::string &in, bool paragraphs)
{
	std::string out;
	std::uint32_t newLine = 0;

	if(paragraphs) out += "<p>";

	struct Local
	{
		std::string &out;
		std::uint32_t &newLine;
		EmoticonData::Map *map;

		Local(std::string &out, std::uint32_t &newLine) : out(out), newLine(newLine), map(NULL) {}
		__inline void term() {
			out += newLine > 1 ? "</p><p>" : (newLine > 0 ? "<br />" : "");
			newLine = 0;
		}

		__inline EmoticonData::Map::Pair *inMap(const std::string &key) {
			auto it = map->map.lower_bound(key);
			if(it!=map->map.end() && it->first==key) return &(*it);
			if(it==map->map.begin()) return NULL;
			--it;
			if(it->first==key.substr(0, it->first.size())) return &(*it);
			return NULL;
		}
	} local(out, newLine);

	auto &emoticon = EmoticonData::instance();

	const char *p = in.c_str();
	for(; *p!='\0'; ++p)
	{
		/// Parse emoticoons
		local.map = emoticon.map(p);
		if(local.map) {
			std::size_t keySize = 1;
			for(; keySize<local.map->maxLen; ++keySize) if(p[keySize] == '\0') break;
			std::string key(p, keySize);
			EmoticonData::Map::Pair *pair = local.inMap(key);
			if(pair) {
				p += pair->first.size() - 1;
				out.append("<img src=\"").append(pair->second).append("\" alt=\"").append(pair->first).append("\" />");
				continue;
			}
		}

		/// Parse everything else
		switch(*p)
		{
		case 10: if(!paragraphs) { out += "<br />"; break; }
			do { ++p; if(*p==13) continue; ++newLine; if(*p!=10) break; } while(1); --p; local.term(); break;
		case 13: break;
		case '\"': out += "&quot;"; break;
		case '&': out += "&amp;"; break;
		case '<': out += "&lt;"; break;
		case '>': out += "&gt;"; break;
		case '[': bbcode(out, p); break;
		default: out += *p;
		}
	}

	if(paragraphs) out += "</p>";

	return out;
}


/// Simple email validation
bool Email::valid(const std::string &email)
{
	const char *b = email.c_str();
	const char *e = b + email.size();
	const char *a = strstr(b, "@");
	if(!a++) return false;

	const char *d = strstr(a, ".");
	if(!d++) return false;

	if(int(a - b) < 1) return false;
	if(int(d - a) < 1) return false;
	if(int(e - d) < 1) return false;

	return true;
}

bool Email::send(const std::string &host, std::uint16_t port, const Poco::Net::MailMessage &message,
	const std::string &username, const std::string &password)
{
	using namespace Poco;
	using namespace Poco::Net;

	try
	{
		SharedPtr<InvalidCertificateHandler> pCert = new Poco::Net::AcceptCertificateHandler(false);
		Context::Ptr pContext = new Context(Context::CLIENT_USE, "", "", "", Context::VERIFY_RELAXED,
			9, true, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
		SSLManager::instance().initializeClient(0, pCert, pContext);

		SecureSMTPClientSession session(host, port);
		session.login();
		session.startTLS(pContext);
		if(!username.empty())
			session.login(SMTPClientSession::AUTH_LOGIN, username, password);

		session.sendMessage(message);
		session.close();
	}
	catch(Poco::Exception& exc)
	{
		printf("Email error: '%s'\n", exc.displayText().c_str());
		return false;
	}

	return true;
}