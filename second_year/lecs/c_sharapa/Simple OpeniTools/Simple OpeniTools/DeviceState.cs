using System;

public class DeviceState
{
    private Dictionary<string, string> _info = new();

    public event Action<Dictionary<string, string>>? onInfoChanged;

    public Dictionary<string, string> info
    {
        get => _info;
        set
        {
            if (_info.Equals(value)) return;
            _info = value;
            onInfoChanged?.Invoke(value);
        }
    }
}
