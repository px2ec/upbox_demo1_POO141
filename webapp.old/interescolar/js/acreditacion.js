function getData(url, round) {
	var query = $.get(url);
	
	var msg = '\n';
	msg += '<img src="img/ajax-loading.gif"';
	msg += ' width="16" height="11"';
	msg += ' alt="">';
	msg += ' Actualizando...\n';
	$("#msgBox").html(msg);
	$("#msgBox").attr("style", "visibility: visible;");

	query.done(function(data, status) {
		var newRowsTp = '\n';
		var newRowsAp = '\n';

		var val = data.equipos;
		for (var i = 0; i < val.length; i++) {
			var textValue;
			switch (val[i][3]) {
				case 0: textValue = "Valparaíso"; break;
				case 1: textValue = "Santiago"; break;
				default: textValue = "Concepción";
			}
			if (val[i][2] == 1) {
				newRowsTp += '<tr>\n';
				newRowsTp += '  <td><a href="javascript:moveDown(' + val[i][0] + ')">Desacreditar</td>\n';
				newRowsTp += '  <td>' + val[i][1] + '</td>\n';
				newRowsTp += '  <td>' + textValue + '</td>\n';
				newRowsTp += '</tr>\n';
			} else {
				newRowsAp += '<tr>\n';
				newRowsAp += '  <td><a href="javascript:moveUp(' + val[i][0] + ')">Acreditar</td>\n';
				newRowsAp += '  <td>' + val[i][1] + '</td>\n';
				newRowsAp += '  <td>' + textValue + '</td>\n';
				newRowsAp += '</tr>\n';
			}
		}

		$("#updateMeTp").html(newRowsTp);
		$("#updateMeAp").html(newRowsAp);
		$("#msgBox").attr("style", "visibility: hidden;");
		return true;
	});

	query.fail(function(data, status) {
		$("#msgBox").html("Error al actualizar!")
		$("#msgBox").attr("style", "visibility: visible;");
		return false;
	});
}

function updateValues(settings)
{
	var running = false;
	this.startStop = function() {
		var link = document.getElementById('updLink');
		if (running == false) {
			link.innerHTML = "Detener";
			running = true;
			action.run();
		} else {
			link.innerHTML = "Actualizar";
			running = false;
			action.freeze();
		}
	}

	var inter;
	var action = {
		refresh: function() {
			getData(settings.url);
		},

		run: function() {
			action.refresh();
			inter = setInterval(action.refresh,
				settings.rfrate);
		},
		
		freeze: function() {
			clearInterval(inter);
		},
	};

	if (!settings.autorun) {
		return false;
	}

	this.startStop();
	return true;
}