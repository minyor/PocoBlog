#ifndef CTRL_FORM_BLOG_H
#define CTRL_FORM_BLOG_H


#include <core/Header.h>
#include <ctrl/Controller.h>


namespace ctrl { namespace form
{
	class Blog : public core::Form
	{
	public:
		enum Mode {MODE_SEARCH=0, MODE_BLOG, MODE_CATEGORY};

	public:
		model::Category category;
		model::Blog blog;
		core::DataID oldCategoryID, oldBlogID;
		core::DataID editPostID;
		std::string searchQuery;
		uint64_t hasSearchResults, hasCategories, hasBlogs;

		core::facet::Paginator paginator;
		core::facet::List sortModes;
		std::int32_t sort;

		core::Vector<model::Category> categoryChain;
		core::Vector<model::Category> categories;
		core::Vector<model::Blog> searchResults;
		core::Vector<model::Blog> blogs;
		core::Tree<model::Post> posts;

	public:
		Blog();
		~Blog();

	public:
		std::string format(const std::string &in, bool paragraphs = false);
		Mode mode();
		std::string param();

	public:
		void onEnter();
		void onLoad();

	private:
		void newCategory(std::istream *stream);
		void newBlog(std::istream *stream);
		void newPost(std::istream *stream);
		void editBlog(std::istream *stream);
		void editPost(std::istream *stream);
		void getContent(std::istream *stream);
		void removeCategory(std::istream *stream);
		void removeBlog(std::istream *stream);
		void removePost(std::istream *stream);
		void ratePost(std::istream *stream);
		void paginate(std::istream *stream);

	public:
		__inline Controller &ctrl() const { return (Controller &)session(); }

	};
}}


#endif // CTRL_FORM_BLOG_H
