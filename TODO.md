## v1.0.0 Release

* move the auth stuff from protocol to auth
* figure out how to handle the rest of the special commands
  * login, hello, logout
  * trace the calls -> multiple entry points?
* figure out how to manage BaseChannel mqtt calls
  * move all the mqtt stuff to ChannelController
  * move all the templated calls from BaseChannel to ChannelController
* general clean up of the protocol class
  * combine generateFoo into their handlers if not used elsewhere
  * global brightness -> needs a controller hook
    * implement hook on rgb
    * implement hook on pwm
  * sendFoo functions -> consolidate the serialization boilerplate
* test that dns and stuff works after improv
* we need some way to indicate that a fast update is needed.

* modify the gulp.js script to pull from the framework lib directory
  * it should also write the files to the framework lib directory for inclusion
  * project specific gulp rules to pull in custom stuff logo, css, js, etc.
      * html/index.html -> overrides framework html
      * html/logo.png -> overrides framework.html
      * html/css/* -> gets added to the framework css includes
      * html/js/* -> gets added to the framework js includes

* fix our CI hooks