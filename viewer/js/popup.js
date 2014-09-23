define(['jquery', 'underscore'], function($, _) {
	// Members
	var element;

	function initialize() {
		// Append to DOM
		element = $('<section class="popup">').appendTo('body');
		element.append('<div class="close">');

		// Events
		element.on('click', '.close', close);
		$(document).on('keydown', function(e) {
			if (e.which == 27)
				close();
		});
	}

	function html(content) {
		element.children().remove();
		element.append('<div class="close">');
		element.append(content);
	}

	function append(content) {
		element.append(content);
	}

	function close() {
		element.hide();
		element.remove();
	}

	function main() {
		initialize();

		// Return reference to element to allow adding content
		return {
			append: append,
			html: html,
			close: close
		};
	}

	return main;
});
