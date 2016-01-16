<%@ impl include="core/Tag.h"%>
<%@ impl include="ctrl/form/Registration.h"%>
<%@ page form="false"%>
<%!PAGE(Registration, PATH("/Registration")CLASS(ctrl::form::Registration))%>

	<%%SESSION%>

	<%TILE_BEGIN("head")%><%@ include page="tile/head.html" %><%TILE_END%>
	<%TILE_BEGIN("topbar")%><%@ include page="tile/topbar.html" %><%TILE_END%>
	<%TILE_BEGIN("header")%><%@ include page="tile/header.html" %><%TILE_END%>
	<%TILE_BEGIN("menu")%><%@ include page="tile/menu.html" %><%TILE_END%>

	<%TILE_BEGIN("content")%>
		<%IF(me["mode"] == "activated")%>
			<h1>Activation Successful!</h1>
			The account for <%=me.newUser->username()%> has been successfully activated!
		<%ELIF(me["mode"] == "inactive" && me.newUser && me.newUser->group() == me.newUser->INACTIVE)%>
			<h1>Registration Successful!</h1>
			Thank you for registering! A confirmation email has been sent to <%=me.newUser->email()%>. Please click on the Activation Link to Activate your account.
			<a href="/*resendActivationEmail">Resend confirmation email?</a>
		<%ELIF(!user)%>
			<h1>Registration:</h1>
			<%=me.captcha.htmlUse()%>
			<form method="POST" action="*signin" id="userForm"><%=CSRF%>
				<div class="userCol1">Username:</div><div class="userCol2"><input type="text" <%=NAME(username)%>></div>
				<div class="userCol1">Email Address:</div><div class="userCol2"><input type="text" <%=NAME(email)%>></div>
				<div class="userCol1">Password:</div><div class="userCol2"><input type="password" <%=NAME(password)%>></div>
				<div class="userCol1">Confirm Password:</div><div class="userCol2"><input type="password" <%=NAME(password2)%>></div>
				<div class="userCol1"><%=me.captcha.htmlQuestion()%></div><div class="userCol2"><%=me.captcha.htmlAnswer()%></div>
				<div class="userCol1"></div><div class="userCol2"><input type="submit" value="Register"></div>
				<div class="userStatus"><span class="userError"><%=me["status"]%></span></div>
			</form><!--Forgot your password?-->
		<%ELSE%>
			<h1>You are already registered.</h1>
		<%ENDIF%>
	<%TILE_END%>

	<%TILE_BEGIN("navigation")%><%@ include page="tile/navigation.html" %><%TILE_END%>
	<%TILE_BEGIN("footer")%><%@ include page="tile/footer.html" %><%TILE_END%>

	<%TEMPLATE("html/template.html")%>
