How to compileOpen Command Prompt 
gcc knowledge_vault.c -o vaultIf compilation succeeds,

 an executable named vault will be created in the same folder.How to runFrom the same folder:On Windows Command Prompt:vault

The main menu will appear in the terminal.

Features implemented

Create notePrompts for a title and a single-line content

.Appends the note to notes.txt in a simple text format.

View all notesReads all notes from notes.txt.

Prints every stored note to the terminal.

Search notesAsks for a keyword.Searches notes for that keyword (in title/content) and prints matching notes.

Edit noteLets the user select a note (for example by ID or order).Allows updating the title and/or content.Rewrites the file so the selected note is replaced with the updated version.

Delete noteLets the user select a note to remove.Rewrites the file without that note.

ExitCleanly exits the program from the menu loop.



Data storage details

All notes are stored in notes.txt in the same folder as the program.
Each note is saved in a simple human-readable text format (for example using lines with TITLE:..., CONTENT:... and separators).

The file is created automatically when the user saves the first note if it does not already exist.