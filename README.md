# DATE Conversions

Convert to and from Microsoft's `DATE` data type used in the `VARIANT` record as `VT_DATE`.

![Build and Test](https://github.com/Patschkowski/dates/actions/workflows/build-and-test.yml/badge.svg)

## References

- [Converting between Windows FILETIME and Unix time_t without having to type the magic number 116444736000000000](https://devblogs.microsoft.com/oldnewthing/20220602-00/?p=106706)
- [VariantTimeToSystemTime function (oleauto.h)](https://learn.microsoft.com/en-us/windows/win32/api/oleauto/nf-oleauto-varianttimetosystemtime)
- [SystemTimeToVariantTime function (oleauto.h)](https://learn.microsoft.com/en-us/windows/win32/api/oleauto/nf-oleauto-systemtimetovarianttime)
- [FileTimeToSystemTime function (timezoneapi.h)](https://learn.microsoft.com/en-us/windows/win32/api/timezoneapi/nf-timezoneapi-filetimetosystemtime)
- [SystemTimeToFileTime function (timezoneapi.h)](https://learn.microsoft.com/en-us/windows/win32/api/timezoneapi/nf-timezoneapi-systemtimetofiletime)
