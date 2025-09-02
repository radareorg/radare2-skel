declare let r2frida: any;

r2frida.pluginRegister('test', function(name: string) {
  if (name === 'test') {
    return function(args: string) {
      console.log('Hello Args From r2frida plugin', args);
      return 'Things Happen';
    }
  }
});
