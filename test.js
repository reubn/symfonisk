let huejay = require('huejay');
console.log('Start');


let client = new huejay.Client({
  host:     '172.19.0.105',
  timeout:  15000,            // Optional, timeout in milliseconds (15000 is the default)
});

client.bridge.get()
  .then(bridge => {
    console.log(`Retrieved bridge ${bridge.name}`);
    console.log('  Id:', bridge.id);
    console.log('  Model Id:', bridge.modelId);
    console.log('  Model Name:', bridge.model.name);
  });

  client.lights.getAll()
    .then(lights => {
      for (let light of lights) {
        // console.log(`Light [${light.id}]: ${light.name}`);
        // console.log(`  Type:             ${light.type}`);
        // console.log(`  Unique ID:        ${light.uniqueId}`);
        // console.log(`  Manufacturer:     ${light.manufacturer}`);
        // console.log(`  Model Id:         ${light.modelId}`);
        // console.log('  Model:');
        // console.log(`    Id:             ${light.model.id}`);
        // console.log(`    Manufacturer:   ${light.model.manufacturer}`);
        // console.log(`    Name:           ${light.model.name}`);
        // console.log(`    Type:           ${light.model.type}`);
        // console.log(`    Color Gamut:    ${light.model.colorGamut}`);
        // console.log(`    Friends of Hue: ${light.model.friendsOfHue}`);
        // console.log(`  Software Version: ${light.softwareVersion}`);
        // console.log('  State:');
        console.log(`    On:         ${light.on}`);
        console.log(`    Reachable:  ${light.reachable}`);
        console.log(`    Brightness: ${light.brightness}`);
        console.log(`    Color mode: ${light.colorMode}`);
        console.log(`    Hue:        ${light.hue}`);
        console.log(`    Saturation: ${light.saturation}`);
        console.log(`    X/Y:        ${light.xy[0]}, ${light.xy[1]}`);
        console.log(`    Color Temp: ${light.colorTemp}`);
        console.log(`    Alert:      ${light.alert}`);
        console.log(`    Effect:     ${light.effect}`);
        console.log();

        light.on = true
        light.effect = /*light.effect === 'colorloop' ? '' : */'colorloop'

        return client.lights.save(light)
      }
    });
