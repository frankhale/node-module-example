const process = require('process');
const world = require('bindings')('helloworld');

console.log(world.hello("World!!!"));

world.foo((msg) => {
  console.log("JS: " + msg);
});

console.log(world.bar());