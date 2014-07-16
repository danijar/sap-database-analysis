define(['jquery', 'underscore', 'connection', 'popup'], function($, _, Connection, Popup) {
	// Members
	var element;
	var datas = {};
	var connections = {};
***REMOVED***
	function initialize(container, root) {
		// Create and attach container
		element = $('<div class="tree">');
		container.html(element);
***REMOVED***
		// Fetch and add root node
		var url = 'http://localhost:8080/fetcher/' + root;
		$.getJSON(url).done(function(data) {
			node(data);
			// Expand first level of children
			$('#' + escape(root) + ' > .inner').click();
		}).error(console.error);
***REMOVED***
		// Events
		element.on('click', '.inner', function() {
			// Lazy load children when clicking a table
			var table = $(this).parent().attr('id');
			toggle(table);
		});
		element.on('click', 'h2', function() {
			// Open structure popup when clicking table name
			var table = $(this).parent().parent().attr('id');
			popup(table);
			
			// Prevent expanding children
			return false;
		});
	}
***REMOVED***
	// Escape special chars for proper id selectors
	function escape(name) {
		var result = "";
		for (var i = 0; i < name.length; i++) {
			if (name[i].match(/[^a-zA-Z0-9-_]/))
				result += '\\';
			result += name[i];
		}
		return result;
	}
***REMOVED***
	// Render a table
	function node(data, parent) {
		// Cache data
		datas[data.id] = data;
***REMOVED***
		// Structure changes
		var difference = $('<div class="difference">');
		if (data.added.length) {
			var added = $('<ul class="added">');
			_.each(data.added.sort(), function(field) {
				added.append('<li>' + field + '</li>');
			});
			difference.append(added);
		}
		if (data.added.length) {
			var removed = $('<ul class="removed">');
			_.each(data.added.sort(), function(field) {
				removed.append('<li>' + field + '</li>');
			});
			difference.append(removed);
		}
***REMOVED***
		// Copies
		var more = $('<span class="more">');
		if (data.names.length > 1)
			more.append('Represents ' + data.names.length + ' tables');
***REMOVED***
		// Table
		var inner = $('<div class="inner">');
		inner.append('<h2>' + data.names[0] + '</h2>');
		inner.append(more);
		inner.append(difference);
***REMOVED***
		// Information about descendants
		var paragraph = '<p>';
		var number = data.children ? data.children.length : 0;
		if (data.amount > number)
			paragraph += data.amount + ' tables ';
		if (number)
			paragraph += number + (number > 1 ? ' children' : ' child');
		paragraph += '</p>';
		inner.append(paragraph);
***REMOVED***
		// Wrapper containing table and children
		var table = $('<div class="table" id="' + data.id + '">');
		table.append(inner);
		table.append('<br>');
		table.append('<div class="children">');
***REMOVED***
		// Append to parent
		if (parent) {
			$('#' + escape(parent) + ' > .children').append(table);
		} else {
			element.append(table);
			document.title = data.names[0];
		}
	}
***REMOVED***
	function toggle(table) {
		var url = 'http://localhost:8080/fetcher/' + table + '/children';
		$.getJSON(url).done(function(children) {
			// Containers
			var tablebox = $('#' + escape(table));
			var childrenbox = tablebox.children('.children');
			var innerbox = tablebox.children('.inner');
***REMOVED***
			// Keep view
			var oldoffset = innerbox.offset();
***REMOVED***
			// Load children
			if (!childrenbox.children().length) {
				_.each(children, function(child) {
					node(child, table);
				});
			}
***REMOVED***
			// Expand or collapse
			if (childrenbox.hasClass('visible')) {
				// Remove line connections
				childrenbox.children().each(function() {
					var key = $(this).attr('id');
					connections[key].remove();
					delete connections[key];
				});
***REMOVED***
				// Hide
				childrenbox.removeClass('visible');
			} else {
				// Show
				childrenbox.addClass('visible');
***REMOVED***
				// Add line connections
				childrenbox.children().each(function() {
					var key = $(this).attr('id');
					connections[key] = Connection(tablebox, $(this), innerbox);
				});
			}
***REMOVED***
			// Restore view
			var newoffset = innerbox.offset();
			$('body').scrollTop($('body').scrollTop() - (oldoffset.top - newoffset.top));
			$('body').scrollLeft($('body').scrollLeft() - (oldoffset.left - newoffset.left));
***REMOVED***
			// Update all connections
			_.each(connections, function(connection) {
				connection.update();
			});
		}).error(function(error) {
			$('.loading').text('An error occured.');
			console.error(error);
		});
	}
***REMOVED***
	function popup(table) {
		var url = 'http://localhost:8080/fetcher/' + table + '/fields';
		$.getJSON(url).done(function(fields) {
			var popup = Popup();
***REMOVED***
			popup.append('<h1>' + datas[table].names[0] + '</h1>');
***REMOVED***
			if (datas[table].names.length > 1) {
				names = datas[table].names[1];
				for (var i = 2; i < datas[table].names.length; i++)
					names += ', ' + datas[table].names[i];
				popup.append('<p class="more">Other names are ' + names + '.</p>');
			}
***REMOVED***
			var rows = '<table><thead><tr><th>Name</th><th>Key</th><th>Type</th><th>Length</th><th>Role</th></tr></thead>';
			rows += '<tbody>';
			_.each(fields, function(field) {
				var key = '';
				if (field.key)
					key = '<span class="key"></span>';
				rows += '<tr><td>' + field.name + '</td><td>' + key + '</td><td>' + field.type + '</td><td>' + field.length + '</td><td>' + field.role + '</tr>';
			});
			rows += '</tbody></table>'
			popup.append(rows);
		}).error(console.error);
	}
***REMOVED***
	function main(container, root) {
		initialize(container, root);
	}
***REMOVED***
	return main;
});
