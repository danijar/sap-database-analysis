define(['jquery', 'underscore', 'text!../../data/root/children.json', 'text!../../data/root/differences.json', 'text!../../data/root/amounts.json'], function($, _, Children, Differences, Amounts) {
	var element, children, differences, amounts, root;
***REMOVED***
	function initialize(container) {
		element = $('<div class="tree">');
		container.append(element);
		
		// Parse input data
		children    = JSON.parse(Children);
		differences = JSON.parse(Differences);
		amounts 	= JSON.parse(Amounts);
***REMOVED***
		// Lazy load children when clicking a table
		$(document).on('click', 'div.inner', function() {
			// Get name
			var current = $(this).parent().attr('id');
***REMOVED***
			// Load children
			var empty = $(this).siblings('.children').children().length < 1; 
			if (empty) {
				_.each(children[current], function(child) {
					table(child, current);
				});
			}
***REMOVED***
			// Expand or collapse
			$(this).siblings('.children').toggleClass('visible');
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
	function table(current, parent) {
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
		var container = $('<div class="table" id="' + current + '">');
		container.append(inner);
		container.append('<br>');
		container.append('<div class="children">');
***REMOVED***
		// Append to parent
		if (parent) 
			$('#' + escape(parent) + ' > .children').append(container);
		else 
			element.append(container);
	}
***REMOVED***
	function main(container, root) {
		initialize(container);
		table(root);
	}
	
	return main;
});
