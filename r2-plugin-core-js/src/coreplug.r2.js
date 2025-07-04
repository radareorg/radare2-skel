r2.plugin("core", function () {
  function penisCall(cmd) {
    if (cmd.startsWith("test")) {
      console.log(r2.cmd("?E Hello from r2js"));
      return true;
    }
    return false;
  }
  return {
    name: "test",
    call: penisCall,
  };
});
