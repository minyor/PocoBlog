<%@ impl include="core/Tag.h"%>
<%@ page form="false"%>
<%!PAGE(Login)%>

	<%%SESSION%>

	<%TILE_BEGIN("head")%><%@ include page="tile/head.html" %><%TILE_END%>
	<%TILE_BEGIN("topbar")%><%@ include page="tile/topbar.html" %><%TILE_END%>
	<%TILE_BEGIN("header")%><%@ include page="tile/header.html" %><%TILE_END%>
	<%TILE_BEGIN("menu")%><%@ include page="tile/menu.html" %><%TILE_END%>

	<%TILE_BEGIN("content")%>
		<%IF(!user)%>
			<h1>Log in:</h1>
			<form method="POST" action="*login"><%=CSRF%>
				<div class="userCol1">Username:</div><div class="userCol2"><input type="text" <%=NAME(username)%>></div>
				<div class="userCol1">Password:</div><div class="userCol2"><input type="password" <%=NAME(password)%>></div>
				<div class="userCol1"></div><div class="userCol2"><input type="submit" value="Log in"></div>
				<div class="userStatus"><span class="userError"><%=me["status"]%></span></div>
			</form>
		<%ELSE%>
			<h1>You are already logged in.</h1>
		<%ENDIF%>
	<%TILE_END%>

	<%TILE_BEGIN("navigation")%><%@ include page="tile/navigation.html" %><%TILE_END%>
	<%TILE_BEGIN("footer")%><%@ include page="tile/footer.html" %><%TILE_END%>

	<%TEMPLATE("html/template.html")%>
