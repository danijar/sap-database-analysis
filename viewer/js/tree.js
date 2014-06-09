define(['jquery', 'underscore', 'connection', 'text!../../data/root/children.json', 'text!../../data/root/differences.json', 'text!../../data/root/amounts.json'], function($, _, Connection, Children, Differences, Amounts) {
	// Members
	var element;
	var children, differences, amounts;
	var connections = {};
***REMOVED***
	function initialize(container, root) {
		// Change window title
		document.title = root;
***REMOVED***
		// Create and attach container
		element = $('<div class="tree">');
		container.append(element);
***REMOVED***
		// Parse input data
		children    = JSON.parse(Children);
		differences = JSON.parse(Differences);
		amounts 	= JSON.parse(Amounts);
***REMOVED***
		// Lazy load children when clicking a table
		$(document).on('click', 'div.inner', function() {
			var table = $(this).parent().attr('id');
			toggle(table);
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
	function node(current, parent) {
		// Structure changes
		var difference = $('<div class="difference">');
		if (differences[current]) {
			if (differences[current][0].length) {
				var added = $('<ul class="added">');
				_.each(differences[current][0], function(field) {
					added.append('<li>' + field + '</li>');
				});
				difference.append(added);
			}
***REMOVED***
			if (differences[current][1].length) {
				var removed = $('<ul class="removed">');
				_.each(differences[current][1], function(field) {
					removed.append('<li>' + field + '</li>');
				});
				difference.append(removed);
			}
		}
***REMOVED***
		// Table
		var inner = $('<div class="inner">');
		inner.append('<h2>' + current + '</h2>');
		inner.append(difference);
***REMOVED***
		// Information about descendants
		var paragraph = '<p>';
		var number = children[current] ? children[current].length : 0;
		if (amounts[current] > number)
			paragraph += amounts[current] + ' tables ';
		if (number)
			paragraph += number + (number > 1 ? ' children' : ' child');
		paragraph += '</p>';
		inner.append(paragraph);
***REMOVED***
		// Wrapper containing table and children
		var table = $('<div class="table" id="' + current + '">');
		table.append(inner);
		table.append('<br>');
		table.append('<div class="children">');
***REMOVED***
		// Append to parent
		var container = parent ? $('#' + escape(parent) + ' > .children') : element;
		container.append(table);
	}
***REMOVED***
	function toggle(table) {
		var tablebox = $('#' + escape(table));
		var childrenbox = tablebox.children('.children');
		var innerbox = tablebox.children('.inner');
***REMOVED***
		// Load children
		var empty = childrenbox.children().length < 1;
		if (empty)
			for (var i = 0; i < children[table].length; ++i)
				node(children[table][i], table);
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
		// Update all connections
		_.each(connections, function(connection) {
			connection.update();
		});
	}
***REMOVED***
	function main(container, root) {
		initialize(container, root);
		node(root);
***REMOVED***
		// Open first level of children
		$('#' + escape(root) + ' > .inner').click();
	}
***REMOVED***
	return main;
});
