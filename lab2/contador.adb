with Ada.Text_IO;
with Ada.Integer_Text_IO;

use Ada.Text_IO;
use Ada.Integer_Text_IO;

procedure Contador is
   X: Integer := 0;
   no_termina1, no_termina2: Boolean := true;

   protected Value is
      entry Agregar;
      entry Obtener(X: out Integer);
   private
      cont: Integer := 0;
   end Value;

   protected body Value is
      entry Agregar when cont >= 0 is
      begin
         cont := cont + 1;
      end Agregar;
      entry Obtener(X: out Integer) when cont >= 0 is
      begin
         X := cont;
      end Obtener;
   end Value;

   task tarea1;
   task tarea2;

   task body tarea1 is
      k: Integer := 0;
   begin
      while k < 1_000_000 loop
         Value.Agregar;
         k := k + 1;
      end loop;
      no_termina1 := false;
   end tarea1;

   task body tarea2 is
      k: Integer := 0;
   begin
      while k < 1_000_000 loop
         Value.Agregar;
         k := k + 1;
      end loop;
      no_termina2 := false;
   end tarea2;

begin
   while no_termina1 or no_termina2 loop
      null;
   end loop;
   put_line("La suma es: ");
   Value.Obtener(X);
   put(X);
end Contador;
