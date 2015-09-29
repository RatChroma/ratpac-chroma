{
  name:"GEO",
  valid_begin: [0,0],
  valid_end: [0,0],
  gdml_file: "mybox.gdml",
  opdet_lv_name: "volTube",
}

{
  name:"GEO",
  index: "border_tank_wall",
  valid_begin: [0,0],
  valid_end: [0,0],
  mother:"border",
  type:"border",
  volume1:"pvSomeBox",
  volume2:"pvBoxContents",
  surface:"stainless_steel",
  reverse:1,
}