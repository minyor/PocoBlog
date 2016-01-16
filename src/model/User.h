#ifndef MODEL_USER_H
#define MODEL_USER_H


#include <core/Header.h>
#include <core/Util.h>


namespace model
{
	class User
	{
	public:
		enum Group { ADMIN = 0, INACTIVE = 1, USER = 2, SUBSCRIBER = 3 };

	public:
		Poco::Nullable<core::UserID> _id;
		std::string _username;
		std::string _password;
		std::string _email;

		std::string _activation_token;
		Poco::DateTime _create_date;
		Poco::DateTime _modify_date;

		std::int16_t _group;
		std::string _first_name;
		std::string _last_name;
		std::string _phone_number;
		std::string _country;
		std::string _state;
		Poco::DateTime _birthday;

	public:
		User();
		~User();

	public:
		explicit operator bool() const;

	public:
		__inline void id(core::UserID val) { val ? (_id = val) : (_id = Poco::NULL_GENERIC); }
		__inline core::UserID id() const { return _id.isNull() ? 0 : (core::UserID)_id; }

		__inline void username(const std::string &val) { _username = val; }
		__inline const std::string &username() const { return _username; }

		__inline void password(const std::string &val) { _password = val; }
		__inline const std::string &password() const { return _password; }

		__inline void email(const std::string &val) { _email = val; }
		__inline const std::string &email() const { return _email; }

		__inline void activationToken(const std::string &val) { _activation_token = val; }
		__inline const std::string &activationToken() const { return _activation_token; }

		__inline void createDate(const Poco::DateTime &val) { _create_date = val; }
		__inline const Poco::DateTime &createDate() const { return _create_date; }

		__inline void modifyDate(const Poco::DateTime &val) { _modify_date = val; }
		__inline const Poco::DateTime &modifyDate() const { return _modify_date; }

		__inline void group(Group val) { _group = (std::int16_t)val; }
		__inline Group group() const { return (Group)_group; }

		__inline void firstName(const std::string &val) { _first_name = val; }
		__inline const std::string &firstName() const { return _first_name; }

		__inline void lastName(const std::string &val) { _last_name = val; }
		__inline const std::string &lastName() const { return _last_name; }

		__inline void phoneNumber(const std::string &val) { _phone_number = val; }
		__inline const std::string &phoneNumber() const { return _phone_number; }

		__inline void country(const std::string &val) { _country = val; }
		__inline const std::string &country() const { return _country; }

		__inline void state(const std::string &val) { _state = val; }
		__inline const std::string &state() const { return _state; }

		__inline void birthday(const Poco::DateTime &val) { _birthday = val; }
		__inline const Poco::DateTime &birthday() const { return _birthday; }

		__inline bool registered() const { return (bool)_id; }

	};
}


#include <core/db/SQLTable.h>


SQLTableBegin(User, model::User)
	SQLColumn(1, _id, "INTEGER PRIMARY KEY")
	SQLColumn(2, _username, "VARCHAR(30)")
	SQLColumn(3, _password, "TEXT")
	SQLColumn(4, _email, "VARCHAR(320)")
	SQLColumn(5, _activation_token, "VARCHAR(25)")
	SQLColumn(6, _create_date, "DATETIME")
	SQLColumn(7, _modify_date, "DATETIME")
	SQLColumn(8, _group, "TINYINT")
	SQLColumn(9, _first_name, "VARCHAR(40)")
	SQLColumn(10, _last_name, "VARCHAR(40)")
	SQLColumn(11, _phone_number, "VARCHAR(50)")
	SQLColumn(12, _country, "VARCHAR(50)")
	SQLColumn(13, _state, "VARCHAR(50)")
	SQLColumn(14, _birthday, "DATETIME")
SQLTableEnd(User)


#endif // MODEL_USER_H
