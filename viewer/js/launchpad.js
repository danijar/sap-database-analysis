define(['jquery', 'underscore', 'text!../../data/root/children.json', 'text!../../data/root/differences.json'], function($, _, Children, Differences) {
	var element, children, differences;
***REMOVED***
	function initialize(container) {
		element = $('<div class="launchpad">');
		container.append(element);
***REMOVED***
		// Parse input data
		children = JSON.parse(Children);
		differences = JSON.parse(Differences);
	}
***REMOVED***
	// Render a tile
	function tile(current) {
		// Remove specialchars for use as id
		var id = current.replace(/[^a-zA-Z0-9-_]/g, '');
***REMOVED***
		// Create node
		var difference = $('<div class="difference">');
		var added = $('<ul class="added">');
		if (differences[id]) {
			if (differences[id][0].length) {
				_.each(differences[id][0], function(field) {
					added.append('<li>' + field + '</li>');
				});
			}
		}
		difference.append(added);
***REMOVED***
		var tile = $('<a class="tile" href="#/table/' + id + '">');
		tile.append('<h2>' + current + '</h2>');
		tile.append(difference);
		tile.append('<p>' + children[current].length + ' children</p>');
***REMOVED***
		element.append(tile);
	}
***REMOVED***
***REMOVED***
	function main(container) {
		initialize(container);
***REMOVED***
		_.each(children['root'], function(head) {
			tile(head);
		});
	}
	
	return main;
});
