const devicedisplayops = require('./build/Release/devicedisplayops');

function convertDateToUTC(date) { return new Date(date.getUTCFullYear(), date.getUTCMonth(), 
	date.getUTCDate(), date.getUTCHours(), date.getUTCMinutes(), date.getUTCSeconds()); }


test('Number of Connected Displays on my machine should be 1', () => {
  	expect(devicedisplayops.getNumOfDisplays()).toBe(1);
});


test('The active display should be detected as On', () => {
  	expect(devicedisplayops.checkActiveDisplayState()).toBe(1);
});


test('Last input time test', async () => {

	devicedisplayops.monitorWake(); // Last input

	let i = devicedisplayops.getLastInputTime();

	await new Promise((i) => setTimeout(i, 5000)); // Wait for 5 seconds

	// Get the date-time 5 seconds ago and convert it in UTC format

	var date = new Date(Date.now() - 5000); 
	var now_utc = convertDateToUTC(date);

	var date = (now_utc.getMonth()+1) + '-' + now_utc.getDate() + '-' + now_utc.getFullYear();
	var time = now_utc.getHours() + ":" + now_utc.getMinutes() + ":" + now_utc.getSeconds();
	var dateTime = date+' '+time;

  	expect(i.trim()).toMatch(dateTime.trim());
});


jest.setTimeout(70000);

test('The active display should be detected as off after a sleep request is sent', async () => {
	
	devicedisplayops.monitorSleep();

	let f = devicedisplayops.checkActiveDisplayState();
	await new Promise((f) => setTimeout(f, 15000));
  	expect(devicedisplayops.checkActiveDisplayState()).toBe(0);

  	let g = devicedisplayops.monitorWake();
  	await new Promise((g) => setTimeout(g, 15000));
});

test('The active display should be detected as on after a wake request is sent', async () => {

	let g = devicedisplayops.monitorSleep();
	await new Promise((g) => setTimeout(g, 15000));

	let h = devicedisplayops.monitorWake();
	await new Promise((h) => setTimeout(h, 10000));

	let i = devicedisplayops.checkActiveDisplayState();
	await new Promise((i) => setTimeout(i, 5000));

  	expect(devicedisplayops.checkActiveDisplayState()).toBe(1);
});

test('The active display should be detected as on after a wake request is sent', async () => {

	let g = devicedisplayops.monitorSleep();
	await new Promise((g) => setTimeout(g, 15000));

	let h = devicedisplayops.monitorWake();
	await new Promise((h) => setTimeout(h, 10000));

	let i = devicedisplayops.checkActiveDisplayState();
	await new Promise((i) => setTimeout(i, 5000));

  	expect(devicedisplayops.checkActiveDisplayState()).toBe(1);
});