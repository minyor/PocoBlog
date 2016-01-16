<%@ impl include="core/Tag.h"%>
<%@ page form="false"%>
<%!PAGE(Index, PATH("/index.html"))%>

	<%%SESSION%>

	<%TILE_BEGIN("head")%><%@ include page="tile/head.html" %><%TILE_END%>
	<%TILE_BEGIN("topbar")%><%@ include page="tile/topbar.html" %><%TILE_END%>
	<%TILE_BEGIN("header")%><%@ include page="tile/header.html" %><%TILE_END%>
	<%TILE_BEGIN("menu")%><%@ include page="tile/menu.html" %><%TILE_END%>

	<%TILE_BEGIN("content")%>
		<h1>London</h1>
		<p>
			London is the capital city of England. It is the most populous city in the United Kingdom,
			with a metropolitan area of over 13 million inhabitants.
		</p>
		<p>
			Standing on the River Thames, London has been a major settlement for two millennia,
			its history going back to its founding by the Romans, who named it Londinium.
		</p>
	<%TILE_END%>

	<%TILE_BEGIN("navigation")%><%@ include page="tile/navigation.html" %><%TILE_END%>
	<%TILE_BEGIN("footer")%><%@ include page="tile/footer.html" %><%TILE_END%>

	<%TEMPLATE("html/template.html")%>
