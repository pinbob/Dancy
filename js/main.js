var GROUP_SIZE = 300;
var SECOND = 1000;//1 second, used for duration

var groupLeft = true;//initial position is center
var groupTop = true;//initial position is center

function init(){
	//show title change
	$("#title").css("left", window.innerWidth / 2 - 120);//centering
	$("#title").hover(function(){
		$("#title").css("background-image", "url('images/dancy1.jpg')");
	}, function(){
		$("#title").css("background-image", "url('images/dancy0.jpg')");
	});
	$("#title").show();

	//set arrow group to center
	centerGroup();
	$("#arrowGroup").fadeIn(2 * SECOND);

	//set main scene
	$("#mainScene").css("width", window.innerWidth - 440);//centerin
	$("#mainScene").css("height", window.innerHeight - 440);

	//set info: 180*60 to center of group
	$(".info").css("left", 150 - 90);
	$(".info").css("top", 150 - 30);
	$("#leftArrow,#rightArrow,#upArrow,#downArrow").mouseout(function(){
		$(".info").fadeOut(SECOND / 2);
	});
	$("#upArrow").mouseenter(function(){
		$("#who").fadeIn(SECOND);
	});
	$("#rightArrow").mouseenter(function(){
		$("#why").fadeIn(SECOND);
	});
	$("#leftArrow").mouseenter(function(){
		$("#how").fadeIn(SECOND);
	});
	$("#downArrow").mouseenter(function(){
		$("#what").fadeIn(SECOND);
	});

	//set mouse events handler
	$("#centerArrow").click(function(){
		centerGroup();
		//hide scene
		$("#mainScene").fadeOut(SECOND, function(){
			showScene(0);
		});
	});
	$("#leftArrow").click(function(){
		//hide scene
		$("#mainScene").fadeOut(SECOND, function(){
			moveGroup(true, groupTop);
			setTimeout("showScene(4)", SECOND);
		});
	});
	$("#rightArrow").click(function(){
		//hide scene
		$("#mainScene").fadeOut(SECOND, function(){
			moveGroup(false, groupTop);
			setTimeout("showScene(2)", SECOND);
		});
	});
	$("#downArrow").click(function(){
		//hide scene
		$("#mainScene").fadeOut(SECOND, function(){
			moveGroup(groupLeft, false);
			setTimeout("showScene(3)", SECOND);
		});
	});
	$("#upArrow").click(function(){
		//hide scene
		$("#mainScene").fadeOut(SECOND, function(){
			moveGroup(groupLeft, true);
			setTimeout("showScene(1)", SECOND);
		});
	});
}

function centerGroup(){
	$("#arrowGroup").css("left", (window.innerWidth - GROUP_SIZE) / 2);
	$("#arrowGroup").css("top", "auto");
}

function moveGroup(isLeft, isTop){
	if (isLeft){
		$("#arrowGroup").animate({
			left: "0"
		}, SECOND / 2);
	}else{
		$("#arrowGroup").animate({
			left: String(window.innerWidth - GROUP_SIZE)
		}, SECOND / 2);
	}
	groupLeft = isLeft;

	if (isTop){
		$("#arrowGroup").animate({
			top: "0"
		}, SECOND / 2);
	}else{
		$("#arrowGroup").animate({
			top: String(window.innerHeight - GROUP_SIZE)
		}, SECOND / 2);
	}
	groupTop = isTop;
}

function showScene(index){
	switch(index){
	case 0:
		return;
	case 4:
		//Who(red)
		$("#mainScene").html("<h1>WHO made it</h1><p>Some content...To be accomplished.</p>");
		$("#mainScene").css("background", "#9d2f2c");
		$("#mainScene").css("background", "-moz-linear-gradient(left,  #9d2f2c 0%, #ab2523 30%, #d45549 100%)");
		$("#mainScene").css("background", "-webkit-gradient(linear, left top, right top, color-stop(0%,#9d2f2c), color-stop(30%,#ab2523), color-stop(100%,#d45549))");
		$("#mainScene").css("background", "-webkit-linear-gradient(left,  #9d2f2c 0%,#ab2523 30%,#d45549 100%)");
		$("#mainScene").css("background", "-o-linear-gradient(left,  #9d2f2c 0%,#ab2523 30%,#d45549 100%)");
		$("#mainScene").css("background", "-ms-linear-gradient(left,  #9d2f2c 0%,#ab2523 30%,#d45549 100%)");
		$("#mainScene").css("background", "linear-gradient(left,  #9d2f2c 0%,#ab2523 30%,#d45549 100%)");
		break;

	case 2:
		//Why(yellow)
		$("#mainScene").html("<h1>WHY would you like it</h1><p>Some content...To be accomplished.</p>");
		$("#mainScene").css("background", "#9a5c0d");
		$("#mainScene").css("background", "-moz-linear-gradient(left,  #9a5c0d 0%,  #d3a11c 100%)");
		$("#mainScene").css("background", "-webkit-gradient(linear, left top, right top, color-stop(0%,#9a5c0d), color-stop(100%,#d3a11c))");
		$("#mainScene").css("background", "-webkit-linear-gradient(left,  #9a5c0d 0%,#d3a11c 100%)");
		$("#mainScene").css("background", "-o-linear-gradient(left,  #9a5c0d 0%,#d3a11c 100%)");
		$("#mainScene").css("background", "-ms-linear-gradient(left,  #9a5c0d 0%,#d3a11c 100%)");
		$("#mainScene").css("background", "linear-gradient(left,  #9a5c0d 0%,#d3a11c 100%)");
		break;

	case 3:
		//What(blue)
		$("#mainScene").html("<h1>WHAT is Dancy</h1><p>Some content...To be accomplished.</p>");
		$("#mainScene").css("background", "#0d57a7");
		$("#mainScene").css("background", "-moz-linear-gradient(left,  #0d57a7 0%, #147db5 100%)");
		$("#mainScene").css("background", "-webkit-gradient(linear, left top, right top, color-stop(0%,#0d57a7), color-stop(100%,#147db5))");
		$("#mainScene").css("background", "-webkit-linear-gradient(left,  #0d57a7 0%,#147db5 100%)");
		$("#mainScene").css("background", "-o-linear-gradient(left,  #0d57a7 0%,#147db5 100%)");
		$("#mainScene").css("background", "-ms-linear-gradient(left,  #0d57a7 0%,#147db5 100%)");
		$("#mainScene").css("background", "linear-gradient(left,  #0d57a7 0%,#147db5 100%)");
		break;

	case 1:
		//How(green)
		$("#mainScene").html("<h1>HOW to play</h1><p>Some content...To be accomplished.</p>");
		$("#mainScene").css("background", "#2c7a11");
		$("#mainScene").css("background", "-moz-linear-gradient(left, #2c7a11 0%, #7ca314 100%)");
		$("#mainScene").css("background", "-webkit-gradient(linear, left top, right top, color-stop(0%,#2c7a11), color-stop(100%,#7ca314))");
		$("#mainScene").css("background", "-webkit-linear-gradient(left, #2c7a11 0%,#7ca314 100%)");
		$("#mainScene").css("background", "-o-linear-gradient(left, #2c7a11 0%,#7ca314 100%)");
		$("#mainScene").css("background", "-ms-linear-gradient(left, #2c7a11 0%,#7ca314 100%)");
		$("#mainScene").css("background", "linear-gradient(left, #2c7a11 0%,#7ca314 100%)");
		break;

	}
	$("#mainScene").fadeIn(SECOND);
}
