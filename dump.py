#!/usr/bin/python3
import factory

ilasm = "/mnt/c/Windows/Microsoft.NET/Framework64/v4.0.30319/ilasm.exe"
ildasm = "/mnt/c/Program Files (x86)/Microsoft SDKs/Windows/v10.0A/bin/NETFX 4.6.1 Tools/ildasm.exe"
cilon_doc_folder = "/mnt/c/Users/Ian/Documents/CilonTemp"
cilon_doc_folder_win = r"C:\Users\Ian\Documents\CilonTemp"

def main():
    factory.AddTarget("test.exe")
    factory.AddDir("ilsrc")
    factory.Add("CilonTest.exe")
    factory.Execute()

@factory.rule
def CompileIL(context):
    """
    %.exe : ilsrc/%.il
        cp $< $(cilon_doc_folder)
        $(ilasm) /EXE $(cilon_doc_folder_win)\\\\test.il  /OUTPUT=$(cilon_doc_folder_win)\\\\$@
        cp $(cilon_doc_folder)/$@ $@
    """

@factory.rule
def DumpIL(context):
    """
    %.ildump : %.exe
        cp $< $(cilon_doc_folder)
        $(ildasm) $(cilon_doc_folder_win)\\\\$< /OUT=$(cilon_doc_folder_win)\\\\$@
        cp $(cilon_doc_folder)/$@ $@
    """


if __name__ == "__main__":
    main()
