function getData(url) {
	var query = $.get(url);
	
	var msg = '\n';
	msg += '<img src="img/ajax-loading.gif"';
	msg += ' width="16" height="11"';
	msg += ' alt="">';
	msg += ' Actualizando...\n';
	$("#msgBox").html(msg);
	$("#msgBox").attr("style", "visibility: visible;");

	query.done(function(data, status) {
		var newRows = '\n';
		var val = data.results;
		for (var i = 0; i < val.length; i++) {
			newRows += '<tr>\n';
			newRows += '  <td>' + val[i][0] + '</td>\n';
			newRows += '  <td>' + val[i][1] + '</td>\n';
			newRows += '  <td>' + val[i][2] + '</td>\n';
			newRows += '  <td>' + val[i][3] + '</td>\n';
			newRows += '  <td>' + val[i][4] + '</td>\n';
			newRows += '  <td>' + val[i][5] + '</td>\n';
			newRows += '  <td>' + val[i][6] + '</td>\n';
			newRows += '</tr>\n';
		}

		$("#updateMe").html(newRows);
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