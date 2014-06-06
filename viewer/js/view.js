define(['jquery', 'underscore', 'text!../../data/root/children.json', 'text!../../data/root/differences.json'], function($, _, Children, Differences) {
	var element, children, differences, root;
***REMOVED***
	function initialize() {
		// Attach to DOM
		element = $('<section class="content">');
		$('body').append(element);
***REMOVED***
		// Parse input data
		children = JSON.parse(Children);
		differences = JSON.parse(Differences);
		root = Children.match(/^{"([^"]+)"/m)[1];
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
	// Iteratively render all tables
	// Currently not used because of performance problems
	var jobs = [];
	function hierarchy(table) {
		// Add job for root table
		jobs.push({ child: table, parent: null });
***REMOVED***
		// Work through all jobs
		// The list will become longer while iterating
		for (var i = 0; i < jobs.length && i < 12000; ++i) {
			var current = jobs[i].child;
			var parent  = jobs[i].parent;
***REMOVED***
			// Remove specialchars for use as id
			var id = current.replace(/[^a-zA-Z0-9-_]/g, '');
***REMOVED***
			// Create node
			var container = $('<div class="table" id="' + id + '">');
			var inner = $('<div class="inner">');
			inner.append('<h2>' + current + '</h2>');
***REMOVED***
			container.append(inner);
			container.append('<br>');
			container.append('<div class="children">');
***REMOVED***
			// Append to parent
			if (parent)
				$('#' + parent + ' > .children').append(container);
			else
				$('.content').append(container);
***REMOVED***
			// Render all children
			for (var j = 0; j < children[current].length; ++j)
				jobs.push({ child: children[current][j], parent: id });
		}
	}
***REMOVED***
	// Render a table
	function table(current, parent) {
		// Remove specialchars for use as id
		var id = current.replace(/[^a-zA-Z0-9-_]/g, '');
***REMOVED***
		// Create node
		var difference = $('<div class="difference">');
		if (differences[id]) {
			if (differences[id][0].length) {
				var added = $('<ul class="added">');
				_.each(differences[id][0], function(field) {
					added.append('<li>' + field + '</li>');
				});
				difference.append(added);
			}
			if (differences[id][1].length) {
				var removed = $('<ul class="removed">');
				_.each(differences[id][1], function(field) {
					removed.append('<li>' + field + '</li>');
				});
				difference.append(removed);
			}
		}
***REMOVED***
		var inner = $('<div class="inner">');
		inner.append('<h2>' + current + '</h2>');
		inner.append(difference);
		inner.append('<p>' + children[current].length + ' children</p>');
***REMOVED***
		var container = $('<div class="table" id="' + id + '">');
		container.append(inner);
		container.append('<br>');
		container.append('<div class="children">');
***REMOVED***
		// Append to parent
		if (parent)
			$('#' + parent + ' > .children').append(container);
		else
			$('.content').append(container);
	}
***REMOVED***
***REMOVED***
	function main() {
		initialize();
		table(root);
	}
	
	return main;
});
