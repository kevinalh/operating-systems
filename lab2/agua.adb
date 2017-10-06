with Ada.Text_IO;
with Ada.Integer_Text_IO;

use Ada.Text_IO;
use Ada.Integer_Text_IO;

procedure Agua is

   task type hAtom is
      entry hReady;
   end hAtom;

   task type oAtom is
      entry oReady;
   end oAtom;

   task body hAtom is
   begin
      accept hReady  do

      end hReady;
   end hAtom;


begin
   null;
end Agua;
