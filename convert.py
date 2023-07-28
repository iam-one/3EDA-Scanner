import numpy as np
from stl import mesh

def readPointCloud(file_path):
    points = []
    with open(file_path, 'r') as file:
        for line in file:
            x, y, z = map(float, line.strip().split(','))
            points.append([x, y, z])
    return np.array(points)

def exportToStl(file_path, vertices):
    triangles = [(vertices[i], vertices[i+1], vertices[i+2]) for i in range(len(vertices) - 2)]
    mesh_data = mesh.Mesh(np.zeros(len(triangles), dtype=mesh.Mesh.dtype))
    for i, triangle in enumerate(triangles):
        for j in range(3):
            mesh_data.vectors[i][j] = triangle[j]

    mesh_data.save(file_path)

if __name__ == "__main__":
    input_file = "point_cloud.txt"
    output_file = "point_cloud.stl"

    point_cloud = readPointCloud(input_file)

    exportToStl(output_file, point_cloud)