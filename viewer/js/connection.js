define(['jquery', 'underscore'], function ($, _) {
	return function(area, from, to) {
		// Private members
		var stroke = 8;
***REMOVED***
		// Add SVG line to DOM
		var x1 = 0;
		var y1 = 0;
		var x2 = 100 + '%';
		var y2 = 100 + '%';
		var svg = $('<svg>'
			+ '<line x1="' + x1 + 'px" y1="' + y1 + 'px" x2="' + x2 + '" y2="' + y2 + '" '
			+ 'style="stroke:#aaa; stroke-width:' + stroke + '" />'
			+ '</svg>').appendTo(area);
***REMOVED***
		// Calculate start point from DOM elements
		function start() {
			var from_offset = from.offset();
			var area_offset = area.offset();
			return {
				x: from_offset.left - area_offset.left + from.outerWidth() / 2,
				y: from_offset.top - area_offset.top
			}
		}
***REMOVED***
		// Calculate end point from DOM elements
		function end() {
			var to_offset = to.offset();
			var area_offset = area.offset();
			return {
				x: to_offset.left - area_offset.left + to.outerWidth() / 2,
				y: to_offset.top - area_offset.top + to.outerHeight() / 2
			}
		}
***REMOVED***
		// Render line and dots to match passed coordinates
		function render(start, end) {
			// Flip in order to draw line from top left to bottom right
			var flip_x = end.x > start.x ? 1 : -1;
			var flip_y = end.y > start.y ? 1 : -1;
***REMOVED***
			// Calculate dimensions
			var width = Math.abs(end.x - start.x);
			width = Math.max(width, stroke);
***REMOVED***
			var height = Math.abs(end.y - start.y);
			// height = Math.max(height, stroke);
			height += stroke;
***REMOVED***
			// Calculate positions
			var left = Math.min(start.x, end.x);
			left += parseInt(area.css('padding-left'));
***REMOVED***
			var top = Math.min(start.y, end.y);
			top += parseInt(area.css('padding-top'));
***REMOVED***
			// Apply to DOM element
			svg.css({
				'width': width,
				'height': height,
				'left': left,
				'top': height,
				'transform': 'scale(' + flip_x + ', ' + flip_y + ')',
			});
		}
***REMOVED***
		// Adapt to changed connection points
		function update() {
			render(start(), end());
		}
***REMOVED***
		// Remove SVG from DOM
		function remove() {
			svg.remove();
		}
***REMOVED***
		update();
***REMOVED***
		return {
			update: update,
			remove: remove
		};
	};
});
