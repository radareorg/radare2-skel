const r2pipe = require('r2pipe-promise');

async function Main() {
	const r2 = await r2pipe.open('/bin/ls');
	const res = await r2.cmd("x");
	console.log(res);
	await r2.quit();
}

Main().then(console.log);
