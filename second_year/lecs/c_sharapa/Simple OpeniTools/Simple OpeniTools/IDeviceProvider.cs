using RustyOptions;
using System;
using static RustyOptions.Result;
using System.Runtime.InteropServices;

public class IDeviceProvider: IDisposable
{
	private IntPtr _provider;

	public static Result<IDeviceProvider, string> create() {
		RustResult provider = IDeviceFFI.get_provider();

		if(Utils.IsNull(provider.ok))
		{

			string? errorMsg = IDeviceFFI.ReadAndFreeString(provider.err);

			if (errorMsg == null)
			{
				return Result.Err<IDeviceProvider, string>("was not able to get the error message");
			}

			return Result.Err<IDeviceProvider, string>(errorMsg);

		}

		return Result.Ok(new IDeviceProvider(provider.ok));
	}

	public IntPtr Provider
	{
		get { return _provider; }
	}

	IDeviceProvider(IntPtr provider) {
		this._provider = provider;
	}
	 public void Dispose() {
		IDeviceFFI.free_provider(this._provider);
	}
}
