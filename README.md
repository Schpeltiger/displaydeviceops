
Node NAN module that manages the device displays and device state in Win7/10.

* All functionalities have been tested using a single-monitor setup.

You will need to globally install node-gyp and windows built tools node modules:

- npm install --global --production windows-build-tools
- npm install --global --node-gyp




To setup and compile, go to the module directory,

- node-gyp configure
- node-gyp build



Important: When running tests, the display will turn off and on for some time due to the display device operations. This is the expected behavior. Refrain from moving the mouse or pressing the keyboard as this will possibly interrupt the last input time function in the test. Total runtime of the tests on my machine is about 90 seconds because of the allowances I put in to detect the monitor state.

To run tests (built with Jest), 

- npm run test
