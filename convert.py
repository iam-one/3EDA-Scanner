import numpy as np
import pyvista as pv

from config import POINTCLOUD_PATH, MESH_PATH

# points = pv.wrap(np.genfromtxt(POINTCLOUD_PATH, delimiter=",", dtype=np.float32))
# mesh = points.reconstruct_surface()
# mesh.save(MESH_PATH)

# ------------------------------------------------------------------------------

# points = pv.wrap(pv.Sphere().points)
# surf = points.reconstruct_surface()

# pl = pv.Plotter(shape=(1, 2))
# pl.add_mesh(points)
# pl.add_title('Point Cloud of 3D Surface')
# pl.subplot(0, 1)
# pl.add_mesh(surf, color=True, show_edges=True)
# pl.add_title('Reconstructed Surface')
# pl.show()

# ------------------------------------------------------------------------------

points = pv.wrap(np.genfromtxt(POINTCLOUD_PATH, delimiter=",", dtype=np.float32))
recons = points.reconstruct_surface()

pl = pv.Plotter(shape=(1, 2))
pl.add_mesh(points)
pl.add_title('Point Cloud of 3D Surface')
pl.subplot(0, 1)
pl.add_mesh(recons, color=True, show_edges=True)
pl.add_title('Reconstructed Surface')
pl.show()