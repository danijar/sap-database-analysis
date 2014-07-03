define(['jquery', 'underscore'], function($, _) {
	// Members
	var element;
***REMOVED***
	function initialize() {
		// Append to DOM
		element = $('<section class="popup">').appendTo('body');
		element.append('<div class="close">');
***REMOVED***
		// Events
		element.on('click', '.close', close);
		$(document).on('keydown', function(e) {
			if (e.which == 27)
				close();
		});
	}
***REMOVED***
	function html(content) {
		element.children().remove();
		element.append('<div class="close">');
		element.append(content);
	}
***REMOVED***
	function append(content) {
		element.append(content);
	}
***REMOVED***
	function close() {
		element.hide();
		element.remove();
	}
***REMOVED***
	function main() {
		initialize();
***REMOVED***
		// Return reference to element to allow adding content
		return {
			append: append,
			html: html,
			close: close
		};
	}
***REMOVED***
	return main;
});
