simple Sink
{
    parameters:
        volatile double serviceTime @unit(s) = default(0);
    gates:
        input in;
        output out;
}