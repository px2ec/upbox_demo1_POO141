$(document).ready(function(event) {
	var url_equipos = "http://127.0.0.1:5000/nomequipos"
	var query = $.get(url_equipos);

	query.done(function(data, status) {
		var selOptions = "";

		equipos = data.equipos;
		for (var i = 0; i < equipos.length; i++) {
			selOptions += '<option value="' + equipos[i] + '">' + equipos[i] +'</option>\n';
		}

		$("#teamName").html(selOptions);
	});
});

$(document).ready(function(event) {
	$("#msgBox").attr("style", "display: none");
	$("#boxResults").attr("style", "display: none");

	$("#buscaEquipo").submit(function(event) {
		/* Previene que el formulario envíe normalmente */
		event.preventDefault();

		var $form = $(this), url = $form.attr("action");
		var posting = $.post(url, $form.serialize());

		posting.done(function(data, status) {
			var rol = data.equipo[0];
			var equipo = data.equipo[1];
			var acreditado = data.equipo[2];
			var integrantes = data.integrantes;

			$("#boxResTitle").html("<h4>" + equipo + "</h4>");
			$("#inTeamId").attr("value", rol);

			var divMbr = '';
			for (var i = 0; i < integrantes.length; i++) {
				divMbr += '<label>Integrante ' + (i + 1) + '</label>\n';
				divMbr += '<input type="text" value="' + integrantes[i] + '" readonly>';
			}
			$("#boxMbr").html(divMbr);

			if (acreditado == 1) {
				document.getElementById("chkBoxAcredita").checked=true;
			} else {
				document.getElementById("chkBoxAcredita").checked=false;
			}

			document.getElementById("inRol").value = rol;
			$("#teamPic").attr("src", "img/equipos/" + rol + ".jpg");

			$("#msgBox").attr("style", "display: none");
			$("#boxResults").attr("style", "display: block");
		});
		posting.fail(function(data, status) {
			$("#msgBox").attr("style", "display: block");
			$("#boxResults").attr("style", "display: none");
		});
	});

	$("#formAcreditar").submit(function(event) {
		event.preventDefault();

		var $form = $(this), url = $form.attr("action");
		var posting = $.post(url, $form.serialize());

		$("#msgBox").html('<p>' + 
			'<img src="img/ajax-loading.gif" height="16" width="16" alt="loader">' +
			'Actualizando...</p>');
		$("#msgBox").attr("style", "display: block");

		posting.done(function(data, status) {
			if (data == "ACREDITADO") {
				$("#msgBox").html("<p>Equipo acreditado!</p>");
			} else {
				$("#msgBox").html("<p>Equipo desacreditado!</p>");
			}
			$("#boxResults").attr("style", "display: none");
		});
		posting.fail(function(data, status) {
			console.log(data);
			$("#msgBox").html("<p>Error al acreditar</p>");
			$("#boxResults").attr("style", "display: none");
		});
	});
});

$(document).ready(function(event) {
/*
	$("#formUploadPic").submit(function(event) {
		event.preventDefault();

		var formData = new FormData($(this)[0]);

		var $form = $(this), url = $form.attr("action");
		var posting = $.ajax({
			url: url,
			data: formData,
			async: false,
			cache: false,
			contentType: false,
			processData: false
		});

		posting.done(function(data, status) {
			document.getElementById("teamPic").src = "img/equipos/" + rol + ".jpg";
		});
		posting.fail(function(data, status) {
			
		});
	});
*/

	$('#inFile').on("change", function(event) {
		var d = new Date();

		var width = $("#teamPic").attr("width");
		var height = $("#teamPic").attr("height");

		$("#teamPic").attr("src", "img/ajax-loading.gif?" + d.getTime());
		$("#teamPic").attr("width", "16");
		$("#teamPic").attr("height", "11");

		var formData = new FormData($("#formUploadPic")[0]);
		var $form = $("#formUploadPic"), url = $form.attr("action");
		var posting = $.ajax({
			type: "POST",
			url: url,
			data: formData,
			async: false,
			cache: false,
        	contentType: false,
        	processData: false
		});

		posting.always(function(data, status) {
			var rol = document.getElementById("inRol").value;
			$("#teamPic").attr("width", width);
			$("#teamPic").attr("height", height);
			$("#teamPic").attr("src", "img/equipos/" + rol + ".jpg?" + d.getTime());
		});
	});
});