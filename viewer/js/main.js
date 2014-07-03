requirejs.config({
    baseUrl: 'js',
    urlArgs: 'time=' + (new Date()).getTime(), // prevent caching for development
    paths: {
        underscore: '../lib/underscore-1.6.0/underscore',
        jquery:     '../lib/jquery-2.1.1/jquery-2.1.1',
        text:       '../lib/text-2.0.12/text',
    },
    shim: {
        jquery: {
            exports: '$',
        },
        underscore: {
            exports: '_',
        },
    }
});
***REMOVED***
require(['tree', 'launchpad'], function(View, Launchpad) {
    var container = $('.container');
***REMOVED***
    // Initialize routes
    var routes = {
        '/?':            function() { Launchpad(container); },
        '/table/(.+)/?': function(table) { View(container, table); },
    };
***REMOVED***
    // Listen to route changes
    $(window).on('hashchange', function() {
        // Find matching route
        var hash = window.location.hash.substr(1);
        for (var i in routes) {
            // Test regex against current route
            var regex = new RegExp('^' + i + '$', 'gm');
            var matches = regex.exec(hash);
            if (matches) {
                // Cleanup old view
                container.children().remove();
***REMOVED***
                // Create view with captured groups
                var args = matches.slice(1, matches.length);
                routes[i].apply(undefined, args);
                return;
            }
        }
        
        // No route found
        console.error("No route matches the hash '" + hash + "'.");
    });
***REMOVED***
    // Load initial view
    $(window).trigger('hashchange');
});
