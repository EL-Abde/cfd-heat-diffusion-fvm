import numpy as np
import matplotlib.pyplot as plt
import glob, re, math

# --- Settings (change these to match your params.hpp) ---
DX, DY, D = 0.1, 0.1, 4.0          # grid spacing and diffusivity
DT = (DX*DX * DY*DY) / (2*D*(DX*DX + DY*DY))   # time step
WIDTH, HEIGHT = 10.0, 10.0         # plate dimensions (mm)
COLORMAP = "viridis"               # try 'hot', 'plasma', 'inferno', etc.
T_MIN, T_MAX = 300, 700            # fixed color scale (if AUTO_SCALE=False)
AUTO_SCALE = False                 # True = per‑frame scaling
CONTOURS = None                    # set to e.g. range(300,701,50) for isotherms

# --- Find files and set up grid ---
files = sorted(glob.glob("output_*.csv"), key=lambda x: int(re.search(r'\d+', x).group()))
if not files:
    print("No output_*.csv files found. Run ./heat_sim first.")
    exit(1)

n = len(files)
cols = math.ceil(math.sqrt(n))
rows = math.ceil(n / cols)
fig, axes = plt.subplots(rows, cols, figsize=(8*cols, 8*rows))
axes = [axes] if n == 1 else axes.flatten()

# --- Read first file to get grid size ---
data0 = np.loadtxt(files[0], delimiter=',')
ny, nx = data0.shape
extent = [0, WIDTH, 0, HEIGHT]

# --- Plot each frame ---
for i, f in enumerate(files):
    data = np.loadtxt(f, delimiter=',')
    step = int(re.search(r'\d+', f).group())
    vmin, vmax = (data.min(), data.max()) if AUTO_SCALE else (T_MIN, T_MAX)
    im = axes[i].imshow(data, cmap=COLORMAP, origin='lower', vmin=vmin, vmax=vmax, extent=extent)
    axes[i].set_title(f"t = {step*DT:.3f} s", fontsize=11)
    axes[i].set_xlabel("x (mm)"); axes[i].set_ylabel("y (mm)")
    if CONTOURS:
        c = axes[i].contour(data, levels=CONTOURS, colors='white', linewidths=0.5, extent=extent, origin='lower')
        axes[i].clabel(c, inline=True, fontsize=8)

# --- Hide unused subplots and add colorbar ---
for i in range(n, len(axes)): fig.delaxes(axes[i])
fig.subplots_adjust(right=0.85, hspace=0.3, wspace=0.3)
cbar_ax = fig.add_axes([0.88, 0.15, 0.02, 0.7])
fig.colorbar(im, cax=cbar_ax, label="Temperature (K)")
plt.suptitle(f"Heat Diffusion", fontsize=14)
plt.savefig("results_FVM.png", dpi=150, bbox_inches='tight')
plt.show()
print("✅ results_FVM.png saved.")