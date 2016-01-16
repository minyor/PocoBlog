<%@ impl include="core/Tag.h"%>
<%@ impl include="ctrl/form/Blog.h"%>
<%@ page form="false"%>
<%!PAGE(Blog, CLASS(ctrl::form::Blog))%>

	<%%SESSION%>

	<%TILE_BEGIN("head")%>
		<%@ include page="tile/head.html" %>
		<link rel="stylesheet" type="text/css" href="markitup/skins/markitup/style.css" />
		<link rel="stylesheet" type="text/css" href="markitup/sets/bbcode/style.css" />
		<script type="text/javascript" src="js/jquery-1.4.3.min.js"></script>
		<script type="text/javascript" src="markitup/jquery.markitup.js"></script>
		<script type="text/javascript" src="markitup/sets/bbcode/set.js"></script>
		<script language="javascript">
		$(document).ready(function()	{
			$('#bbcode_blog').markItUp(myBbcodeSettings);
			$('#emoticons a').click(function() {
				emoticon = $(this).attr("title");
				$.markItUp( { replaceWith:emoticon } );
			});
		});
		</script>
	<%TILE_END%>

	<%TILE_BEGIN("topbar")%><%@ include page="tile/topbar.html" %><%TILE_END%>
	<%TILE_BEGIN("header")%><%@ include page="tile/header.html" %><%TILE_END%>
	<%TILE_BEGIN("menu")%><%@ include page="tile/menu.html" %><%TILE_END%>

	<%TILE_BEGIN("content")%>

		<!-- Create categories chain -->
		<a class="categoryChain" href="<%=page.path()%>?c=0">root</a>
		<%FOREACHI(cat, me.categoryChain)%>
			 : <a class="categoryChain" href="<%=page.path()%>?c=<%=cat.id()%>"><%=me.format(cat.title())%></a>
		<%ENDFOR%>

		<!-- Sorting method selector -->
		<%COPY_BEGIN("sortingMethodSelector")%>
			<div class="userCol1">Sort by</div><div class="userCol2">
				<select onchange="location = '*paginate?s='.concat(this.value);">
					<%OPTIONS(me.sortModes)%>
				</select>
			</div>
		<%COPY_END%>

		<!-- Paginator -->
		<%COPY_BEGIN("paginator")%>
			<div class="userCol1">
				<a class="paginatorChain" href="*paginate?p=<%=me.paginator.first()%>">First</a>
				<a class="paginatorChain" href="*paginate?p=<%=me.paginator.prev()%>">Prev</a>
				<%FOREACH(ind, me.paginator.indices)%>
					<a class="paginatorChain<%=ind==me.paginator.page()?" paginatorCurrent":""%>" href="*paginate?p=<%=ind%>"><%=ind%></a>
				<%ENDFOR%>
				<a class="paginatorChain" href="*paginate?p=<%=me.paginator.next()%>">Next</a>
				<a class="paginatorChain" href="*paginate?p=<%=me.paginator.last()%>">Last</a>
			</div>
		<%COPY_END%>

		<!-- Emoticons -->
		<%COPY_BEGIN("emoticons")%>
			<div id="emoticons">
				<%FOREACH(emo, core::server().conf().emoticons())%>
					<a href="#" onclick="return false;" title="<%=emo.name%>"><img src="<%=emo.src%>" /></a>
				<%ENDFOR%>
			</div>
		<%COPY_END%>


		<!-- Search Results mode -->
		<%IF(me.mode() == me.MODE_SEARCH)%>
			<%IF(me.searchResults->size())%>
				<h1>Search Results:</h1>

				<!-- Add sorting method selector -->
				<%PASTE("sortingMethodSelector")%>

				<!-- Print list of Search Results -->
				<%FOREACH(blog, me.searchResults)%>
					<div class="blogListRow">
						<a class="postRowWhole" href="<%=page.path()%>?b=<%=blog.id()%>"><%=blog.title()%></a>
					</div>
				<%ENDFOR%>
			<%ELSE%>
				<h1>Nothing Found</h1>
				Sorry, but nothing matched your search criteria.
			<%ENDIF%>

			<!-- Show more results button -->
			<%IF(me.paginator.hasMore())%>
				<form method="POST" action="*paginate"><%=CSRF%>
					<div class="userCol1"><input type="submit" value="Show More"></div><div class="userCol2"></div>
				</form>
			<%ENDIF%>
		<%ENDIF%>


		<!-- Blog mode -->
		<%IF(me.mode() == me.MODE_BLOG)%>
			<!-- Add blog node to category chain -->
			 : <%=me.format(me.blog.title())%>

			<!-- Pring blog title, date, username, rating and content -->
			<h1><%=me.format(me.blog.title())%></h1>
			<i><b>Posted: </b><%=core::to_string(me.blog.date())%> by <%=me.blog.post().user().username()%></i>
			<br /><a class="postRowValue" href="*ratePost?p=<%=me.blog.post().id()%>"><%=me.blog.post().rated() ? "&#x2935" : "&#x2934"%>+<%=me.blog.post().rating()%></a>
			<%IF(user.group() == user.ADMIN)%>
				<div>
					<a class="postRowOptionR" href="*removeBlog?b=<%=me.blog.id()%>" onclick=
						"return confirm('Are you sure you want to remove this blog?');"><i>Remove</i></a>
					<a class="postRowOptionR" href="#" onclick="createEditBlogBlock(this.parentNode, <%=me.blog.id()%>, <%=me.blog.post().id()%>); return false;"><i>Edit</i></a>
				</div>
			<%ENDIF%>
			<br /><%=me.format(me.blog.post().content(), true)%>

			<!-- Add sorting method selector -->
			<%PASTE("sortingMethodSelector")%>

			<!-- Add Comment button -->
			<form method="POST" action="#"><%=CSRF%>
				<div class="userCol1"><input type="submit" value="Add Comment" onclick="createReplyBlock(null, 0, ''); deleteThis(this); return false;"></div>
				<div class="userCol2"></div>
			</form>

			<!-- Container for cloning Reply Section into -->
			<div id="replyBlockRoot"></div>

			<!-- Print Comments tree -->
			<%TREE_FOREACH(post, me.posts)%>
				<div class='<%=post.parentId() ? "postChildRow" : "postRow"%>'>
					<i><b>Posted: </b><%=core::to_string(post.date())%> by <%=post.user().username()%></i>
					<br /><%=me.format(post.content())%>
					<br /><a class="postRowValue" href="*ratePost?p=<%=post.id()%>"><%=post.rated() ? "&#x2935" : "&#x2934"%>+<%=post.rating()%></a>
					<a class="postRowValue" href="#" onclick="createReplyBlock(this.parentNode, <%=post.id()%>, '<%=post.user().username()%>'); return false;"><i>Reply</i></a>

					<%IF(user.id() == post.user().id() || user.group() == user.ADMIN)%>
						<div>
							<a class="postRowOptionR" href="*removePost?p=<%=post.id()%>" onclick=
								"return confirm('Are you sure you want to remove this comment?');"><i>Remove</i></a>
							<a class="postRowOptionR" href="#" onclick="createEditBlock(this.parentNode, <%=post.id()%>); return false;"><i>Edit</i></a>
						</div>
					<%ENDIF%>

					<%TREE_CHILDREN%>
				</div>
			<%TREE_ENDFOR%>

			<!-- Show more comments button -->
			<%IF(me.paginator.hasMore())%>
				<form method="POST" action="*paginate"><%=CSRF%>
					<div class="userCol1"><input type="submit" value="Show More"></div><div class="userCol2"></div>
				</form>
			<%ENDIF%>


			<!-- Reply Section template (Invisible, for clonning only) -->
			<div id="replyBlock" style="display: none;">
				<form method="POST" action="*newPost"><%=CSRF%>
					<input type="hidden" class="ParentPostIdPar" <%=NAME(pp)%>>
					<%IF(!user)%><div class="userCol1">Email Address:</div><div class="userCol2"><input type="text" <%=NAME(email)%>></div><%ENDIF%>
					<div class="userStatus"><textarea name="content" class="ParentPostContent"><%=me["content"]%></textarea></div>
					<div class="userCol1"><!-- Add Emoticons --><%PASTE("emoticons")%></div>
					<div class="userCol2"><input type="submit" class="ParentPostCancel" onclick="deleteHtmlBlock(this); return false;" value="Cancel">
						<input type="submit" value="Add Comment"></div>
				</form>
				<div class="userStatus"><span class="userError"><%=me["status"]%></span></div>
			</div>

			<!-- Edit Comment Section template (Invisible, for clonning only) -->
			<div id="editBlock" style="display: none;">
				<form method="POST" action="*editPost"><%=CSRF%>
					<input type="hidden" class="ParentPostIdPar" <%=NAME(p)%>>
					<div class="userStatus"><textarea name="content" class="ParentPostContent"><%=me["content"]%></textarea></div>
					<div class="userCol1"><!-- Add Emoticons --><%PASTE("emoticons")%></div>
					<div class="userCol2"><input type="submit" class="ParentPostCancel" onclick="deleteHtmlBlock(this); return false;" value="Cancel">
						<input type="submit" value="Save"></div>
				</form>
				<div class="userStatus"><span class="userError"><%=me["status"]%></span></div>
			</div>

			<!-- Edit Blog Section template (Invisible, for clonning only) -->
			<div id="editBlogBlock" style="display: none;">
				<form method="POST" action="*editBlog"><%=CSRF%>
					<input type="hidden" class="ParentPostIdPar" <%=NAME(b)%>>
					<div class="userCol1">Title:</div><div class="userCol2"><input type="text" class="EditBlogTitle" <%=NAME(title)%>></div>
					<div class="userStatus"><textarea name="content" class="ParentPostContent"><%=me["content"]%></textarea></div>
					<div class="userCol1"><!-- Add Emoticons --><%PASTE("emoticons")%></div>
					<div class="userCol2"><input type="submit" class="ParentPostCancel" onclick="deleteHtmlBlock(this); return false;" value="Cancel">
						<input type="submit" value="Save"></div>
				</form>
				<div class="userStatus"><span class="userError"><%=me["status"]%></span></div>
			</div>
		<%ENDIF%>


		<!-- Blog/Category listing mode -->
		<%IF(me.mode() == me.MODE_CATEGORY)%>
			<p>
				<!-- Add sorting method selector -->
				<%PASTE("sortingMethodSelector")%>

				<!-- Draw paginator -->
				<%PASTE("paginator")%>

				<!-- Print list of Categories -->
				<%FOREACH(cat, me.categories)%>
					<div class="categoryListRow">
						<a class="postRowWhole" href="<%=page.path()%>?c=<%=cat.id()%>"><%=me.format(cat.title())%></a>
						<%IF(user.group() == user.ADMIN)%>
							<a class="postRowOption" href="*removeCategory?c=<%=cat.id()%>" onclick=
								"return confirm('Are you sure you want to remove this category?');"><i>Remove</i></a>
						<%ENDIF%>
					</div>
				<%ENDFOR%>

				<!-- Print list of Blogs -->
				<%FOREACH(blog, me.blogs)%>
					<div class="blogListRow">
						<a class="postRowWhole" href="<%=page.path()%>?b=<%=blog.id()%>"><%=me.format(blog.title())%></a>
						<%IF(user.group() == user.ADMIN)%>
							<a class="postRowOption" href="*removeBlog?b=<%=blog.id()%>" onclick=
								"return confirm('Are you sure you want to remove this blog?');"><i>Remove</i></a>
						<%ENDIF%>
					</div>
				<%ENDFOR%>

				<!-- Draw paginator -->
				<%PASTE("paginator")%>
			</p>

			<!-- New Blog and New Category Sections -->
			<%IF(user && user.group() == user.ADMIN)%>
				<%IF(!me.hasBlogs)%>
					<br /><br /><br />
					<form method="POST" action="*newCategory"><%=CSRF%>
						<div class="userCol1">Title:</div><div class="userCol2"><input type="text" <%=NAME(title)%>></div>
						<div class="userCol1"></div><div class="userCol2"><input type="submit" value="Create new category"></div>
					</form>
				<%ENDIF%>

				<%IF(!me.hasCategories)%>
					<br /><br /><br />
					<!--<textarea id="bbcode" cols="80" rows="20"></textarea>-->
					<form method="POST" action="*newBlog"><%=CSRF%>
						<div class="userCol1">Title:</div><div class="userCol2"><input type="text" <%=NAME(title)%>></div>
						<div class="userStatus"><textarea id="bbcode_blog" name="content"><%=me["content"]%></textarea></div>
						<div class="userCol1"><!-- Add Emoticons --><%PASTE("emoticons")%></div>
						<div class="userCol2"><input type="submit" value="Create new blog"></div>
					</form>
				<%ENDIF%>
				<div class="userStatus"><span class="userError"><%=me["status"]%></span></div>
			<%ENDIF%>
		<%ENDIF%>

	<%TILE_END%>

	<%TILE_BEGIN("navigation")%><%@ include page="tile/navigation.html" %><%TILE_END%>
	<%TILE_BEGIN("footer")%><%@ include page="tile/footer.html" %><%TILE_END%>

	<%TEMPLATE("html/template.html")%>
