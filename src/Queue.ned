simple Queue
{
    parameters:
        string mode;
        int forkNumber = default(0);
    gates:
		input in[];
        output out[];
}