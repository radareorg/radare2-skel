import r2ai

print("Hello World from r2ai")
try:
  res = r2_cmd("?e hello world from r2").strip()
  print(f"RES({res})")
  res = runline(None, "-m")
  print(f"RES({res})")
  res = runline2(None, "-m")
  print(f"RES({res})")
except:
  traceback.print_exc()
