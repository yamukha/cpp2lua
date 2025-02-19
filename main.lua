local lunajson = require 'lunajson'
function converter(val)
      local jobj = lunajson.decode(val)
      jobj[1] = 11
      jobj[2] = 22
      jobj[3] = 33
      jobj[4] ['x']= 44
      return lunajson.encode(jobj)
end
