simple Create
{
    parameters:
        volatile double intervalTime @unit(s) = default(0);
    gates:
        output out;
}