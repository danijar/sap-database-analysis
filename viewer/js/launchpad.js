define(['jquery', 'underscore', 'text!../../data/root/children.json', 'text!../../data/root/differences.json', 'text!../../data/root/amounts.json'], function($, _, Children, Differences, Amounts) {
	var element, children, differences, amounts;
***REMOVED***
	function initialize(container) {
		element = $('<div class="launchpad">');
		container.append(element);
***REMOVED***
		// Parse input data
		children 	= JSON.parse(Children);
		differences = JSON.parse(Differences);
		amounts 	= JSON.parse(Amounts);
	}
***REMOVED***
	// Render a tile
	function tile(current) {
		// Create node
		var difference = $('<div class="difference">');
		var added = $('<ul class="added">');
		if (differences[current]) {
			if (differences[current][0].length) {
				_.each(differences[current][0], function(field) {
					added.append('<li>' + field + '</li>');
				});
			}
		}
		difference.append(added);
***REMOVED***
		var tile = $('<a class="tile" href="#/table/' + current + '">');
		tile.append('<h2>' + current + '</h2>');
		tile.append(difference);
		tile.append('<p>' + amounts[current] + ' tables</p>');
***REMOVED***
		element.append(tile);
	}
***REMOVED***
***REMOVED***
	function main(container) {
		initialize(container);
***REMOVED***
		// Sort head tables by cluster size
		var heads = children['<root>'];
		heads = _.sortBy(heads, function(head) {
			return amounts[head];
		});
		heads.reverse();
***REMOVED***
		// Add head tables as tiles
		_.each(heads, function(head) {
			tile(head);
		});
	}
	
	return main;
});
