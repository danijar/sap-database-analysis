define(['jquery', 'underscore', 'text!../../data/root/children.json'], function($, _, Children) {
	var element, children, root;
***REMOVED***
	function initialize() {
		// Attach to DOM
		element = $('<section class="content">');
		$('body').append(element);
***REMOVED***
		// Parse input data
		children = JSON.parse(Children);
		root = Children.match(/^{"([^"]+)"/m)[1];
	}
***REMOVED***
	function node(current, parent) {
		// Limit number of calls for debug
		if ($('.table').length > 200)
			return;
***REMOVED***
		// Create node
		var container = $('<div class="table" id="' + current + '">');
		var inner = $('<div class="inner">');
		inner.append('<h2>' + current + '</h2>');
***REMOVED***
		container.append(inner);
		container.append('<br>');
		container.append('<div class="children">');
***REMOVED***
		// Append to parent
		if (parent)
			$('#' + parent + ' .children').append(container);
		else
			$('.content').append(container);
***REMOVED***
		// Recursively add children
		_.each(children[current], function(child) {
			node(child, current);
		});
	}
***REMOVED***
***REMOVED***
	function main() {
		initialize();
***REMOVED***
		console.log(children);
		console.log(root);
***REMOVED***
		node(root);
	}
	
	return main;
});
