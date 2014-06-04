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
require(['view'], function(View) {
    View();
});
