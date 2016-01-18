<%@ impl include="core/Tag.h"%>
<%@ page form="false"%>
<%!PAGE(Download)%>

	<%%SESSION%>

	<%TILE_BEGIN("head")%><%@ include page="tile/head.html" %><%TILE_END%>
	<%TILE_BEGIN("topbar")%><%@ include page="tile/topbar.html" %><%TILE_END%>
	<%TILE_BEGIN("header")%><%@ include page="tile/header.html" %><%TILE_END%>
	<%TILE_BEGIN("menu")%><%@ include page="tile/menu.html" %><%TILE_END%>

	<%TILE_BEGIN("content")%>
		<h1>Download</h1>
		<p>
			not implemented yet.
		</p>
	<%TILE_END%>

	<%TILE_BEGIN("navigation")%><%@ include page="tile/navigation.html" %><%TILE_END%>
	<%TILE_BEGIN("footer")%><%@ include page="tile/footer.html" %><%TILE_END%>

	<%TEMPLATE("html/template.html")%>
