# Cities of Emerald — Working Agreement

This repo is the **Cities of Emerald** ROM hack, built on `rh-hideout/pokeemerald-expansion` (`upcoming` branch). Design lives in `docs/CITIES_OF_EMERALD_GDD.md`; build order lives in `docs/IMPLEMENTATION_PLAN.md`.

## Rules (read first, every session)

1. **Ask before acting.** Before editing anything, summarize the task, list the files you plan to change, and wait for Rocco's approval.
2. **Respect status tags** in the GDD. Build only **[DECIDED]** items. For **[PROPOSED]** or **[OPEN]** items, stop and ask.
3. **Verify, don't invent.** Config names and paths in the docs are best-known references. Search the repo to confirm them. If something doesn't exist, report it and propose options.
4. **One task at a time.** One task = one Git branch = one or more small commits.
5. **Every task ends with:** a successful build, the relevant tests passing, a short manual test checklist for Rocco to run in mGBA, and a summary of what changed.
6. **Flag decisions.** If a task forces a design choice, surface it instead of resolving it silently.
7. **Never commit ROM files** (`*.gba`, `*.sav` from real games) or copyrighted assets not already in the repo.
8. **Language:** all new player-facing text uses plain language and avoids ableist wording.
9. **Update the GDD** only when Rocco approves a design change, and change the status tag accordingly.

## Build

```bash
# Toolchain: ARM GNU 14.3.rel1 at ~/opt/arm-gnu-toolchain-14.3.rel1-darwin-arm64-arm-none-eabi/bin (on PATH via ~/.zshrc)
make -j$(sysctl -n hw.ncpu)     # produces pokeemerald.gba
make check -j$(sysctl -n hw.ncpu)  # run the test suite
```

Test in mGBA (`/Applications/mGBA.app`). Base branch: `cities/main`. Upstream remote: `RHH`.
