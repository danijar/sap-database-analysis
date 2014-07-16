define(['jquery', 'underscore'], function($, _) {
	var element, amounts;
***REMOVED***
	function initialize(container, root) {
		// Change window title
		document.title = 'SAP Database Analysis';
		
		// Fetch and render input data
		container.html('<div class="loading">Loading...</div>');
		var url = 'http://localhost:8080/fetcher/' + root + '/children/summary';
		$.getJSON(url).done(function(json) {
			// Sort head tables by cluster size
			data = _.sortBy(json, 'amount');
			data.reverse();
***REMOVED***
			// Create and attach container
			element = $('<div class="launchpad">');
			container.html(element);
***REMOVED***
			// Add head tables as tiles
			_.each(data, tile);
		}).error(function(error) {
			$('.loading').text('An error occured.');
			console.error(error);
		});
	}
***REMOVED***
	// Render a tile
	function tile(current) {
		// Tile
		var tile = $('<a class="tile" href="#/table/' + current.id + '">');
		tile.append('<h2>' + current.names[0] + '</h2>');
		tile.append('<p>' + (current.amount + 1) + ' tables</p>');
***REMOVED***
		element.append(tile);
	}
***REMOVED***
	function main(container, root) {
		initialize(container, root);
	}
***REMOVED***
	return main;
});
