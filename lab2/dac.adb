with Ada.Text_IO;
with Ada.Integer_Text_IO;

use Ada.Text_IO;
use Ada.Integer_Text_IO;

-- a) La tarea1 debe terminar antes que, la tarea2 y la tarea3 empiecen.
-- b) La tarea2 debe terminar antes que la tarea4 empiece.
-- c) La tarea5 debe empezar después que la tarea2, y la tarea3 terminen.

procedure dac is
   cont: Integer := 0;

   task tarea1 is
      entry fin1;
   end tarea1;

   task tarea2 is
      entry fin2;
   end tarea2;

   task tarea3 is
      entry fin3;
   end tarea3;

   task tarea4 is
   end tarea4;

   task tarea5;

   task body tarea1 is
      k: Integer := 0;
   begin
      for k in Integer range 1..10 loop
         put("Tarea1 ");
      end loop;
      for i in Integer range 1..2 loop
         accept fin1 do
            null;
         end fin1;
      end loop;
   end tarea1;

   task body tarea2 is
      k: Integer := 0;
   begin
      tarea1.fin1;
      for k in Integer range 1..10 loop
         put("Tarea2 ");
      end loop;
      for i in 1..2 loop
         accept fin2 do
            null;
         end fin2;
      end loop;
   end tarea2;

   task body tarea3 is
      k: Integer := 0;
   begin
      tarea1.fin1;
      for k in Integer range 1..10 loop
         put("Tarea3 ");
      end loop;
      accept fin3 do
         null;
      end fin3;
   end tarea3;

   task body tarea4 is
      k: Integer := 0;
   begin
      tarea2.fin2;
      for k in Integer range 1..10 loop
         put("Tarea4 ");
      end loop;
   end tarea4;

   task body tarea5 is
      k: Integer := 0;
   begin
      tarea3.fin3;
      tarea2.fin2;
      for k in Integer range 1..10 loop
         put("Tarea5 ");
      end loop;
   end tarea5;

begin
   null;
end dac;
