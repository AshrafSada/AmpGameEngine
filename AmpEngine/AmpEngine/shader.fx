float4 vsmain(float4 pPosition : POSITION) : SV_Position
{
    return pPosition;
}

float4 psmain(float4 pPosition : POSITION) : SV_Target
{
    return float4(0.8f, 0.9f, 0.4f, 1.0f);
}
