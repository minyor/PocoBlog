
var sneaky = new ScrollSneak(location.hostname);

function scrollSneakCallback(e) {
	var e = window.e || e;
	//if(e.target.tagName !== 'A' && e.target.tagName !== 'input') return;
	sneaky.sneak();
}

if(document.addEventListener) document.addEventListener('click', scrollSneakCallback, false);
else document.attachEvent('onclick', scrollSneakCallback);

function httpRequest(url, callback) {
	var request;
	if(window.XMLHttpRequest) request = new XMLHttpRequest();
	else request = new ActiveXObject("Microsoft.XMLHTTP");
	request.onreadystatechange = function() {
		if(request.readyState==4 && request.status==200) callback(request.responseText);
	};
	request.open("GET", url, true);
	request.send(null);
}

function prepareArea(area) {
	$(area).markItUp(myBbcodeSettings);
	$('#emoticons a').click(function() {
		emoticon = $(this).attr("title");
		$.markItUp( { replaceWith:emoticon } );
	});
}

function deleteThis(block) {
	block.outerHTML = ""; delete block;
}
function deleteParent(elem) {
	var block = elem.parentNode;
	block.outerHTML = ""; delete block;
}
function deleteHtmlBlock(elem) {
	var block = elem.parentNode.parentNode;
	block.outerHTML = ""; delete block;
}
function createHtmlBlock(elem, postID, blockID) {
	var putInto = elem; if(!putInto) putInto = document.getElementById('replyBlockRoot');
	if(elem && putInto.getElementsByClassName("ParentPostIdPar").length > 0)
		return deleteHtmlBlock(putInto.getElementsByClassName("ParentPostIdPar")[0]);
	var newelement = document.getElementById(blockID).cloneNode(true);
	putInto.appendChild(newelement);
	newelement.id = ""; newelement.style.display = "block";
	newelement.getElementsByClassName("ParentPostIdPar")[0].value = postID;
	if(!elem) newelement.getElementsByClassName("ParentPostCancel")[0].style.display = "none";
	var area = newelement.getElementsByClassName("ParentPostContent")[0];
	prepareArea(area);
	area.focus();
	return newelement;
}
function createReplyBlock(elem, postID, username) {
	var newelement = createHtmlBlock(elem, postID, 'replyBlock');
	var area = newelement.getElementsByClassName("ParentPostContent")[0];
	if(username != "" && area.innerHTML.charAt(0) != "+") {
		var oldVal = area.innerHTML;
		area.innerHTML = "+".concat(username, " ", oldVal);
	}
}
function createEditBlock(elem, postID) {
	var newelement = createHtmlBlock(elem, postID, 'editBlock');
	var area = newelement.getElementsByClassName("ParentPostContent")[0];
	httpRequest("*getContent?p=".concat(postID.toString()),
		function(response) { area.innerHTML = response; }
	);
}
function createEditBlogBlock(elem, blogID, postID) {
	var newelement = createHtmlBlock(elem, blogID, 'editBlogBlock');
	var area = newelement.getElementsByClassName("ParentPostContent")[0];
	httpRequest("*getContent?p=".concat(postID.toString()),
		function(response) { area.innerHTML = response; }
	);
	var title = newelement.getElementsByClassName("EditBlogTitle")[0];
	httpRequest("*getContent?b=".concat(blogID.toString()),
		function(response) { title.value = response; }
	);
}

