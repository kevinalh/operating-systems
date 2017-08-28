with Ada.Text_IO;
with Ada.Integer_Text_IO;
with LabExercises;

procedure Welcome is
   use LabExercises;
   package IO renames Ada.Text_IO;
   package I_IO renames Ada.Integer_Text_IO;
   Number: Integer;
   Text: String(1 .. 100);
begin
   IO.Put("Test primality: ");
   I_IO.Get(Number);
   IO.Put_Line(Boolean'Image(Is_Prime(Number => Number)));

   IO.Put("Get all primes below: ");
   I_IO.Get(Number);
   Print_Primes_Up_To(Number => Number);

   IO.Put("Fibonacci number: ");
   I_IO.Get(Number);
   IO.Put_Line(Positive'Image(Fibonacci(Number)));

   IO.Put("Factorial: ");
   I_IO.Get(Number);
   IO.Put_Line(Positive'Image(Factorial(Number)));

   IO.Put_Line("Text to read: ");
   IO.Put_Line("WOW");
   --IO.Get_Line(Item => Text, Last => Number);
   --IO.New_Line(1);
   --IO.Put_Line("Text read:" & Text);
end Welcome;
