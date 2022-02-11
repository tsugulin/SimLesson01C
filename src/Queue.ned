simple Queue
{
    parameters:
        volatile int forkNumber = default(0);
    gates:
		input in[];
        output out[];
}