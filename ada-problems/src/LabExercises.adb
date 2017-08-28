with Ada.Text_IO;
with Ada.Numerics.Generic_Elementary_Functions;

package body LabExercises is

   function Is_Prime (Number: Positive) return Boolean is
      Primality: Boolean := True;
   begin
      if Number > 2 then
         for i in 2 .. Number-1 loop
            if Number mod i = 0 then
               Primality := False;
               exit;
            end if;
         end loop;
      end if;
      return Primality;
   exception
      when Constraint_Error =>
         Ada.Text_IO.Put_Line("The number must be positive");
         return False;
   end Is_Prime;

   procedure Print_Primes_Up_To (Number: in Positive) is
      package Math is new Ada.Numerics.Generic_Elementary_Functions(Float_Type => Float);
      package IO renames Ada.Text_IO;
      type Bool_Array is array (Integer range 1 .. Number) of Boolean
        with Default_Component_Value => True;
      Primes: Bool_Array;
      j: Integer;
   begin
      for i in 2 .. Positive(Float'Ceiling(Math.Sqrt(Float(Number)))) loop
         if Primes(i) = True then
            j := i**2;
            while j <= Number loop
               Primes(j) := False;
               j := j + i;
            end loop;
         end if;
      end loop;
      for i in Bool_Array'Range loop
         if Primes(i) = True then
            IO.Put(Positive'Image(i) & ' ');
         end if;
      end loop;
      IO.New_Line(1);
   end Print_Primes_Up_To;

   -- Return the nth fibonacci number

   function Fibonacci (Number: Positive) return Positive is
      Fib, FibBehind, Tmp: Positive := 1;
   begin
      for i in 3 .. Number loop
         Tmp := Fib;
         Fib := Fib + FibBehind;
         FibBehind := Tmp;
      end loop;
      return Fib;
   end Fibonacci;

   function Factorial (Number: Positive) return Positive is
      Fac: Positive := 1;
   begin
      for i in 1 .. Number loop
         Fac := Fac * i;
      end loop;
      return Fac;
   end Factorial;

end LabExercises;
