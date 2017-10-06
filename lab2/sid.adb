with Ada.Text_IO;
with Ada.Integer_Text_IO;

use Ada.Text_IO;
use Ada.Integer_Text_IO;

-- Three kinds of threads:
-- Searchers: They examine the list and can do execute concurrently to each other.
-- Inserters: They add new items to the end of the list (mutex, but can proceed in
-- parallel to searchers.
-- Deleters: They remove items from anywhere in the list. Mutex with searchers
-- and inserters.
procedure SID is
   type Stored is new Integer;
   type Node;
   type Pointer is access Node;
   BufferSize: constant Positive := 10;
   subtype ListIndex is Positive range 1 .. BufferSize;

   type Node is
      record
         Value: Stored;
         Next: Pointer;
      end record;

   type List is
      record
         Head: Pointer;
         Tail: Pointer;
         Size: Natural;
      end record;

   protected type PList is
      function Examine (Index: in ListIndex) return Stored;
      entry Insert (Value: in Integer);
      entry Delete (Index: in Positive);
   private
      Object: List;
   end PList;

   protected body PList is
      function Examine (Index: in ListIndex) return Stored is
         Current: ListIndex := 1;
         Iterator: Pointer := Object.Head;
      begin
         if Index > Object.Size then
            return -1;
         else
            while Current < Index loop
               Iterator := Iterator.Next;
               Current := Current + 1;
            end loop;
            return Iterator.Value;
         end if;
      end Examine;

      entry Insert (Value: in Integer) is
         when
      entry Delete (Index: in Positive);
   end PList;

   task type Searcher;
   task type Inserter;
   task type Deleter;

   task body Searcher is

   end Searcher;



end SID;
