<%@ impl include="core/Tag.h"%>
<%@ impl include="ctrl/form/User.h"%>
<%@ page form="false"%>
<%!PAGE(User, CLASS(ctrl::form::User))%>

	<%%SESSION%>

	<%TILE_BEGIN("head")%>
		<%@ include page="tile/head.html" %>
		<link rel="stylesheet" type="text/css" href="css/calendar.css">
		<script type='text/javascript' src='js/calendar.js'></script>
		<script type='text/javascript' src='js/countries.js'></script>
	<%TILE_END%>

	<%TILE_BEGIN("topbar")%><%@ include page="tile/topbar.html" %><%TILE_END%>
	<%TILE_BEGIN("header")%><%@ include page="tile/header.html" %><%TILE_END%>
	<%TILE_BEGIN("menu")%><%@ include page="tile/menu.html" %><%TILE_END%>

	<%TILE_BEGIN("content")%>

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


		<!-- User settings mode -->
		<%IF(me.mode() == me.MODE_SETTINGS)%>
			<%IF(user)%>

				<%IF(user.group() == user.ADMIN)%>
					<a class="paginatorChain" href="<%=page.path()%>?m=users">&gt; Administer &lt;</a>
				<%ENDIF%>

				<h1>Settings</h1>
				<form method="POST" action="*updateUser"><%=CSRF%>
					<div class="userCol1">FirstName:</div><div class="userCol2"><input type="text" <%=NAME(firstName)%>></div>
					<div class="userCol1">LastName:</div><div class="userCol2"><input type="text" <%=NAME(lastName)%>></div>
					<div class="userCol1">PhoneNumber:</div><div class="userCol2"><input type="text" <%=NAME(phoneNumber)%>></div>

					<div class="userCol1">Country:</div><div class="userCol2"><select id="country" <%=NAME(country)%>></select></div>
					<div class="userCol1">State:</div><div class="userCol2"><select id="state" <%=NAME(state)%>></select></div>
					<script type="text/javascript">populateCountries("country", "state", "<%=me["country"]%>", "<%=me["state"]%>");</script>

					<div class="userCol1">Birthday:</div><div class="userCol2"><input type="text" id="date" <%=NAME(birthday)%>></div>
					<script type="text/javascript">calendar.set("date");</script>

					<div class="userCol1"></div><div class="userCol2"><input type="submit" value="Update"></div>
					<div class="userStatus"><span class="userError"><%=me["status"]%></span></div>
				</form>
			<%ELSE%>
				<h1>Please register.</h1>
			<%ENDIF%>
		<%ENDIF%>


		<!-- User listing mode -->
		<%IF(me.mode() == me.MODE_USERS)%>

			<a class="paginatorChain" href="<%=page.path()%>">&gt; Return to Settings &lt;</a>

			<p>
				<!-- Draw paginator -->
				<%PASTE("paginator")%>

				<!-- Print table of Users -->
				<div class="AdminUsersContainer">
					<%TABLE(cell, me.userTable)%>
						<%=cell%>
					<%ENDTABLE%>
				</div>

				<!-- Remove user btn -->
				<a class="postRowOptionR" href="*removeUser" onclick=
					"return confirm('Are you sure you want to remove this user?');"><i>Remove</i></a>

				<!-- Change user group list -->
				<div class="postRowOptionR">
					<select onchange="location = '*updateGroup?g='.concat(this.value);">
						<%OPTIONS(me.userGroups)%>
					</select>
				</div>

				<!-- Draw paginator -->
				<%PASTE("paginator")%>
			</p>
		<%ENDIF%>

	<%TILE_END%>

	<%TILE_BEGIN("navigation")%><%@ include page="tile/navigation.html" %><%TILE_END%>
	<%TILE_BEGIN("footer")%><%@ include page="tile/footer.html" %><%TILE_END%>

	<%TEMPLATE("html/template.html")%>
