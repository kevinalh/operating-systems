with Ada.Text_IO;
with Ada.Integer_Text_IO;

use Ada.Text_IO;
use Ada.Integer_Text_IO;

procedure Banner is

   task tarea1;
   task tarea2;
   task tarea3;
   task tarea4;
   task tarea5;

   protected Impresion is
      entry Turno1;
      entry Turno2;
      entry Turno3;
      entry Turno4;
      entry Turno5;
      procedure NextTurn;
   private
      Current: Natural := 0;
   end Impresion;

   protected body Impresion is

      procedure NextTurn is
      begin
         Current := (Current + 1) mod 5;
      end NextTurn;

      entry Turno1 when Current = 0 is
      begin
         null;
      end Turno1;

      entry Turno2 when Current = 1 is
      begin
         null;
      end Turno2;

      entry Turno3 when Current = 2 is
      begin
         null;
      end Turno3;

      entry Turno4 when Current = 3 is
      begin
         null;
      end Turno4;

      entry Turno5 when Current = 4 is
      begin
         null;
      end Turno5;

   end Impresion;

   task body tarea1 is
      k: Integer := 0;
   begin
      while k < 100 loop
         Impresion.Turno1;
         put("INF");
         k := k+1;
         Impresion.NextTurn;
      end loop;
   end tarea1;

   task body tarea2 is
      k: Integer := 0;
   begin

      while k < 100 loop
         Impresion.Turno2;
         put("239");
         k := k+1;
         Impresion.NextTurn;
      end loop;

   end tarea2;

   task body tarea3 is
      k: Integer := 0;
   begin

      while k < 100 loop
         Impresion.Turno3;
         put(" SISTEMAS");
         k := k+1;
         Impresion.NextTurn;
      end loop;

   end tarea3;

   task body tarea4 is
      k: Integer := 0;
   begin

      while k < 100 loop
         Impresion.Turno4;
         put(" OPERATIVOS");
         k := k+1;
         Impresion.NextTurn;
      end loop;

   end tarea4;

   task body tarea5 is
      k: Integer := 0;
   begin

      while k < 100 loop
         Impresion.Turno5;
         new_line;
         k := k+1;
         Impresion.NextTurn;
      end loop;

   end tarea5;

begin
   null;
end Banner;
